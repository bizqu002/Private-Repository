var bodyParser		= require('body-parser');    // get body-parser
var Feedback = require('../models/peerEvaluation');


module.exports = function(app, express) 
{

  var apiRouter = express.Router();

  apiRouter.route('/evaluations')

      .post(function(req, res)
      {
        var feedback = new Feedback() ;
        var obj = req.body ;

        for (var i in obj)
        {
          feedback.answers.push({ question: obj[i].question, answer: obj[i].answer }) ;
          console.log(obj[i]) ;
        }

        feedback.save(function(err) {
          if (err) {
            return res.send(err) ;
          }

          res.json({ message: 'Feedback Saved!' }) ;
        });

      });


	  
	  apiRouter.route('/peer')
		.get(function(req,res){
			peerEval.getPeerEvaluations(function(err,data){
				if(err)
					res.send(err);
				res.json(data);
			});
		});
		
		
  return apiRouter
};


		
