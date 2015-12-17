// Djkstra's algorithm for a shortest path routing module in floodlight

package net.floodlightcontroller.myrouting;

import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;

import org.openflow.protocol.OFFlowMod;
import org.openflow.protocol.OFMatch;
import org.openflow.protocol.OFMessage;
import org.openflow.protocol.OFPacketIn;
import org.openflow.protocol.OFType;
import org.openflow.protocol.action.OFAction;
import org.openflow.protocol.action.OFActionOutput;

import net.floodlightcontroller.core.FloodlightContext;
import net.floodlightcontroller.core.IOFMessageListener;
import net.floodlightcontroller.core.IOFSwitch;
import net.floodlightcontroller.core.module.FloodlightModuleContext;
import net.floodlightcontroller.core.module.FloodlightModuleException;
import net.floodlightcontroller.core.module.IFloodlightModule;
import net.floodlightcontroller.core.module.IFloodlightService;
import net.floodlightcontroller.core.IFloodlightProviderService;
import net.floodlightcontroller.devicemanager.IDevice;
import net.floodlightcontroller.devicemanager.IDeviceService;
import net.floodlightcontroller.devicemanager.SwitchPort;

import java.util.ArrayList;
import java.util.Set;

import net.floodlightcontroller.linkdiscovery.ILinkDiscoveryService;
import net.floodlightcontroller.linkdiscovery.LinkInfo;
import net.floodlightcontroller.packet.Ethernet;
import net.floodlightcontroller.packet.IPv4;
import net.floodlightcontroller.routing.Link;
import net.floodlightcontroller.routing.Route;
import net.floodlightcontroller.routing.RouteId;
import net.floodlightcontroller.staticflowentry.IStaticFlowEntryPusherService;
import net.floodlightcontroller.topology.NodePortTuple;

import org.openflow.util.HexString;
import org.openflow.util.U8;
import org.python.google.common.primitives.Ints;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;



class Vertex implements Comparable<Vertex>
{
    public final int name;
    public long id = 0;
    public int ip;
    public Edge[] adjacencies;
    public double minDistance = Double.POSITIVE_INFINITY;
    public Vertex previous;
    public Vertex(int n) { name = n; }
    //public String toString() { return "" + name; }
   
    public int compareTo(Vertex other)
    {
        return Double.compare(minDistance, other.minDistance);
    }

}

class Edge
{
    public final Vertex target;
    public final double weight;
    public Edge(Vertex argTarget, double argWeight)
    { target = argTarget; weight = argWeight; }
}

public class MyRouting implements IOFMessageListener, IFloodlightModule {

    protected IFloodlightProviderService floodlightProvider;
    protected Set<Long> macAddresses;
    protected static Logger logger;
    protected IDeviceService deviceProvider;
    protected ILinkDiscoveryService linkProvider;

    protected Map<Long, IOFSwitch> switches;
    protected Map<Link, LinkInfo> links;
    protected Collection<? extends IDevice> devices;

    protected static int uniqueFlow;
    protected ILinkDiscoveryService lds;
    protected IStaticFlowEntryPusherService flowPusher;
    protected boolean printedTopo = false;

    @Override
    public String getName() {
        return MyRouting.class.getSimpleName();
    }

    @Override
    public boolean isCallbackOrderingPrereq(OFType type, String name) {
        return (type.equals(OFType.PACKET_IN)
                && (name.equals("devicemanager") || name.equals("topology")) || name
                    .equals("forwarding"));
    }

    @Override
    public boolean isCallbackOrderingPostreq(OFType type, String name) {
        return false;
    }

    @Override
    public Collection<Class<? extends IFloodlightService>> getModuleServices() {
        return null;
    }

    @Override
    public Map<Class<? extends IFloodlightService>, IFloodlightService> getServiceImpls() {
        return null;
    }

    @Override
    public Collection<Class<? extends IFloodlightService>> getModuleDependencies() {
        Collection<Class<? extends IFloodlightService>> l = new ArrayList<Class<? extends IFloodlightService>>();
        l.add(IFloodlightProviderService.class);
        l.add(IDeviceService.class);
        l.add(ILinkDiscoveryService.class);
        return l;
    }

    @Override
    public void init(FloodlightModuleContext context) throws FloodlightModuleException
    {
        floodlightProvider = context.getServiceImpl(IFloodlightProviderService.class);
        deviceProvider = context.getServiceImpl(IDeviceService.class);
        linkProvider = context.getServiceImpl(ILinkDiscoveryService.class);
        flowPusher = context.getServiceImpl(IStaticFlowEntryPusherService.class);
        lds = context.getServiceImpl(ILinkDiscoveryService.class);

    }

    @Override
    public void startUp(FloodlightModuleContext context)
    {
       
        floodlightProvider.addOFMessageListener(OFType.PACKET_IN, this);
       
    }

    @Override
    public net.floodlightcontroller.core.IListener.Command receive(IOFSwitch sw, OFMessage msg, FloodlightContext cntx)
    {
   
        // eth is the packet sent by a switch and received by floodlight.
        Ethernet eth = IFloodlightProviderService.bcStore.get(cntx, IFloodlightProviderService.CONTEXT_PI_PAYLOAD);
       
   
       
        // We process only IP packets of type 0x0800.
        if (eth.getEtherType() != 0x0800)
        {
   
            return Command.CONTINUE;
       
        }
       
        else
        {
        	 
                // Print the topology if not yet.
                if (!printedTopo)
                {
                    links = linkProvider.getLinks();
                    Map<Long, Set<Link>> switches = linkProvider.getSwitchLinks(); //prints switches and hosts
                    System.out.println("*** Print topology");
                    for(Long l: switches.keySet())
                    {                    	
                        System.out.print("switch " + l + " neighbors: ");
                        //print neighbors
                        for(Link s : switches.get(l))
                        {
                            if(l != s.getDst())
                            	System.out.print(s.getDst() + ", ");
                        }
                        System.out.println();
                    }
                    printedTopo = true;
               
                } 
                      
                // Parse the packet and obtained source and destination IPs.
                OFPacketIn pi = (OFPacketIn)msg;
                OFMatch match = new OFMatch();
                match.loadFromPacket(pi.getPacketData(), pi.getInPort());   
                int srcIP = match.getNetworkSource();
                int dstIP = match.getNetworkDestination();
                               
                String str1 = Arrays.toString(IntegerToDottedDecimal(srcIP));
                String str2 = Arrays.toString(IntegerToDottedDecimal(dstIP));
                char[] split1 = str1.toCharArray();
                char[] split2 = str2.toCharArray();
                String src = "";
                for(int i = 0; i < split1.length; i++)
                {
                    if(split1[i] == '[' || split1[i] == ']' || split1[i] == ' ');
                    else if(split1[i] == ',')
                        src += '.';
                    else
                        src += split1[i];
                }
                String dst = "";
                for(int i = 0; i < split2.length; i++)
                {
                    if(split2[i] == '[' || split2[i] == ']' || split2[i] == ' ');
                    else if(split2[i] == ',')
                        dst += '.';
                    else
                        dst += split2[i];
                }
                System.out.println("\n*** New packet\nsrcIP: " + src + "\ndstIP: " + dst);
               
                return Command.STOP;
        
   
        }
    }



        // generate and place routing rules
        private void installRoute(List<NodePortTuple> temp, OFMatch match)
        {

            OFMatch stoTMatch = new OFMatch(); /**/
            stoTMatch.setDataLayerType(Ethernet.TYPE_IPv4).setNetworkSource(match.getNetworkSource()).setNetworkDestination(match.getNetworkDestination());

            for (int indx = 0; indx <= temp.size() - 1; indx += 2)
            {
                short inport = temp.get(indx).getPortId();
                stoTMatch.setInputPort(inport);
                List<OFAction> actions = new ArrayList<OFAction>();
                OFActionOutput outport = new OFActionOutput(temp.get(indx + 1).getPortId());
                actions.add(outport);

                OFFlowMod stoDst = (OFFlowMod) floodlightProvider.getOFMessageFactory().getMessage(OFType.FLOW_MOD);
                stoDst.setCommand(OFFlowMod.OFPFC_ADD)
                    .setIdleTimeout((short) 0)
                    .setHardTimeout((short) 0)
                    .setMatch(stoTMatch)
                    .setPriority((short) 105)
                    .setActions(actions)
                    .setLength(
                            (short) (OFFlowMod.MINIMUM_LENGTH + OFActionOutput.MINIMUM_LENGTH));
            flowPusher.addFlow("routeFlow" + uniqueFlow, stoDst,
                    HexString.toHexString(temp.get(indx).getNodeId()));
            uniqueFlow++;
           
        }
       
    }

    byte[] IntegerToDottedDecimal(int bytes)
    {
        return new byte[]
        {
                (byte)((bytes >>> 24) & 0xff),
                (byte)((bytes >>> 16) & 0xff),
                (byte)((bytes >>>  8) & 0xff),
                (byte)((bytes       ) & 0xff)
        };
       
    }
}
       
   
       
