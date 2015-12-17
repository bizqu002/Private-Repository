var bodyParser    = require('body-parser');    // get body-parser
var User          = require('../models/user');
var config        = require('../../config/config');
var UserReg       = require('../models/userRegistration');

/*
 |--------------------------------------------------------------------------
 | Login Required Middleware
 |--------------------------------------------------------------------------
 */
 function ensureAuthenticated(req, res, next) {
  if (!req.headers.authorization) {
    return res.status(401).send({ message: 'Please make sure your request has an Authorization header' });
  }
  var token = req.headers.authorization.split(' ')[1];

  var payload = null;
  try {
    payload = jwt.decode(token, config.TOKEN_SECRET);
  }
  catch (err) {
    return res.status(401).send({ message: err.message });
  }

  if (payload.exp <= moment().unix()) {
    return res.status(401).send({ message: 'Token has expired' });
  }
  req.user = payload.sub;
  next();
}

module.exports = function(app, express) {

  var apiRouter = express.Router();

    // on routes that end in /reports
    // ----------------------------------------------------
    apiRouter.route('/me')
    /*
    |--------------------------------------------------------------------------
    | GET /api/me
    |--------------------------------------------------------------------------
    */
    .get(ensureAuthenticated, function(req, res) {
      User.findById(req.user, function(err, user) {
        res.send(user);
    });
    })

    .put(ensureAuthenticated, function(req, res) {
        User.findById(req.user, function(err, user) {
            if (!user) {
              return res.status(400).send({ message: 'User not found' });
          }
          user.displayName = req.body.displayName || user.displayName;
          user.email = req.body.email || user.email;
          user.save(function(err) {
              res.status(200).end();
          });
      });
    });
    //end of /me route

    apiRouter.route('/users')


        // create a user (accessed at POST http://localhost:8080/users)
        .post(function(req, res) {

            var user = new UserReg();    // create a new instance of the User model
            user.f_name     = req.body.f_name;  // set the users name (comes from the request)
            user.m_name     = req.body.m_name;  // set the users middle name
            user.l_name     = req.body.l_name;  // set the users last name
            user.pID        = req.body.pID;     // set the users panther ID
            user.username   = req.body.username;  // set the users username (comes from the request)
            user.password   = req.body.password;  // set the users password (comes from the request)
            user.email      = req.body.email;   // sets the users email
            user.project    = req.body.project; // sets the users project
            user.cell       = req.body.cell;    // set the users cell phone #
            user.Rank       = req.body.Rank;    // set the users Rank within the program
            user.Major      = req.body.Major;   // sets the users Major
            user.Ethnicity  = req.body.Ethnicity;   // sets the users ethnicity
            user.visaStatus = req.body.visaStatus;  // sets the users visa status
            user.piApproval = req.body.piApproval;
            user.staffApproval = req.body.staffApproval;

            user.save(function(err) {
                if (err) {
                    // duplicate entry
                    if (err.code == 1100)
                        return res.json({ success: false, message: 'A user with that username already exists. '});
                    else
                        return res.send(err);

                }

                // return a message

                res.json({ message: 'User created!' });
            });

        })

        // get all the users (accessed at GET http://localhost:8080/api/users)
        .get(function(req, res) {
            UserReg.find({}, function(err, users) {
                if (err) res.send(err);

                // return the users
                res.json(users);
            });
        })

        // remove the user from the project
        .put(function(req, res){

            UserReg.findById(req.body.userId, function(err, user){
                    if(err) res.send(err);

                    if(!req.body.project){

                        user.project = "Unassigned"
                    }
                    else{
                        user.project= req.body.project;
                    }

                // save the user
                user.save(function(err) {
                    if (err) res.send(err);

                    // return a message
                    res.json({ message: 'User updated!' });
                });

            })
        });



    // on routes that end in /users/:user_id
    // ----------------------------------------------------
    apiRouter.route('/users/:user_id')

        //// get the user with that id
        //.get(function(req, res) {
        //    User.findById(req.params.user_id, function(err, user) {
        //        if (err) res.send(err);
        //
        //        // return that user
        //        res.json(user);
        //    });
        //})

        //// update the user with this id
        //.put(function(req, res) {
        //    User.findById(req.params.user_id, function(err, user) {
        //
        //        if (err) res.send(err);
        //
        //        // set the new user information if it exists in the request
        //        if (req.body.name) user.name = req.body.name;
        //        if (req.body.username) user.username = req.body.username;
        //        if (req.body.password) user.password = req.body.password;
        //
        //        // save the user
        //        user.save(function(err) {
        //            if (err) res.send(err);
        //
        //            // return a message
        //            res.json({ message: 'User updated!' });
        //        });
        //
        //    });
        //})

        // delete the user with this id
        .delete(function(req, res) {
            User.remove({
                _id: req.params.user_id
            }, function(err, user) {
                if (err) res.send(err);

                res.json({ message: 'Successfully deleted' });
            });
        });

    /*
     // create reusable transporter object using SMTP transport
     var transporter = nodemailer.createTransport({
     host:'a2plcpnl0330.prod.iad2.secureserver.net',
     port:465,
     secure:true,
     auth: {
     user: 'nodemail@amcustomprints.com',
     pass: 'spaceCC120'
     }
     });
     // NB! No need to recreate the transporter object. You can use
     // the same transporter object for all e-mails
     // setup e-mail data with unicode symbols
     var mailOptions = {
     from: 'Fred Foo ? <nodemail@amcustomprints.com>', // sender address
     to: 'mrowe122@gmail.com', // list of receivers
     subject: 'Hello ?', // Subject line
     text: req.body.question1 + "</br><b>Hello world ?</b>" +
     req.body.question2 // plaintext body
     };
     // send mail with defined transport object
     transporter.sendMail(mailOptions, function(error, info){
     if(error){
     return console.log(error);
     }
     console.log('Message sent: ' + info.response);
     });
     */

    return apiRouter;
};