angular.module('appRoutes', ['ui.router'])

.config(function($urlRouterProvider, $stateProvider, $locationProvider){
	$urlRouterProvider.otherwise('/');

	$stateProvider
	.state('home', {
		url:'/',
		templateUrl: "views/pages/home.html"
	})
	//signin page
	.state('signin', {
		url:'/signin',
		templateUrl: "views/pages/signin.html",
		controller: "SignInCtrl"
	})
	//sign out page
	.state('signout', {
		url:'/signout',
		templateUrl: "views/pages/signout.html",
		controller: "SignOutCtrl"
	})
	//registration page
	.state('register', {
		url:'/register',
		templateUrl:"views/pages/register.html",
	})
	//about page
	.state('about',{
		url:'/about',
		templateUrl: "views/pages/about.html"
	})
    //faculty msg
	.state('notifications', {
        url: '/notifications',
        templateUrl: '/views/pages/notifications.html',
        controller: 'notificationsController',
        controllerAs: 'notifications'
    })

    .state('snotifications', {
        url: '/snotifications',
        templateUrl: '/views/pages/snotifications.html',
        controller: 'snotificationsController',
        controllerAs: 'snotifications'
    })

	//programs page
	.state('programs',{
		url:'/programs',
		templateUrl: "views/pages/programs.html"
	})
	//user profile
	.state('profile',{
		url: '/profile',
		templateUrl: "views/pages/profile.html",
		controller: 'ProfileCtrl',
		controllerAs: 'sub'
	})
	//6 month reporting
	.state('report',{
		url: '/report',
		templateUrl: "views/pages/report.html",
		controller: 'reportController',
		controllerAs: 'cReport'
	})
	//members page
	.state('membershipReport',{
		url: '/membership_report',
		templateUrl: "views/pages/membershipReport.html",
		controller: 'memberController',
		controllerAs: 'member'
	})
	// groups page
	.state('groups', {
		url: '/groups',
		templateUrl:'/views/pages/groups.html',
		controller: 'userController',
		controllerAs: 'user'
	})
	//create user page
	.state('create', {
		url: '/create',
		templateUrl:'/views/pages/create.html',
		controller: 'userCreateController',
		controllerAs: 'user'
	})
	//create project page
	.state('projects', {
		url: '/projects',
		templateUrl:'/views/pages/projects.html',
		controller: 'projectsController'
	})
	//create project page
	.state('projectCreate', {
		url: '/projects/create',
		templateUrl:'/views/pages/project-create.html',
		controller: 'projectsController'
	})
	.state('edit', {
		url: '/projects/edit/:project_id',
		templateUrl:'/views/pages/project-edit.html',
		controller: 'projectsEditController'
	})
		.state('proposal-feedback', {
			url: '/proposal-feedback',
			templateUrl: '/views/pages/proposal-feedback.html',
			controller: 'projectsController', //changed from feedbackController
			controllerAs: 'feedback'
		})
		.state('viewProject',{
			url: '/proposal-feedback/:project_id',
			templateUrl: '/views/pages/proposal-view.html',
			controller: 'projectsEditController'//, //changed from viewController
			//controllerAs: 'selected'
	})
			.state('registration', {
				url:'/registration',
				templateUrl: "views/pages/registration.html",
				controller: 'userCreateController',
				controllerAs:'cUser'
			})

			.state('piverification', {
				url:'/piverification/:user_id',
				templateUrl: "views/pages/piVerification.html",
				controller: 'verificationController',
				controllerAs: 'vUser'
			})

			.state('verification',{
				url:'/verification/:user_id',
				templateUrl: "views/pages/emailVerification.html",
				controller: 'verificationController',
				controllerAs: 'vUser'
			})
	.state('partial_reports',{
		url: '/proposal-report',
		templateUrl: '/views/pages/report2.html',
	    	controller: 'projectsController'
	})

			.state('resume', {
				url:'/resume',
				templateUrl: "views/pages/resume.html",
				controller: 'resumeController',
				controllerAs:'cUser'
			})

		.state('facultyproject', {
			url: '/facultyproject',
			templateUrl: "views/pages/facultyprojects.html",
			controller: 'facultyController',
			controllerAs: 'fUser'
		})

		.state('piAcceptance', {
			url: '/piAcceptance',
			templateUrl: "views/pages/piAcceptance.html",
			controller: 'piController',
			controllerAs: 'piUser'
		})

		.state('projectEvaluation', {
		url: '/projectEvaluation',
		templateUrl: 'views/pages/projectEvaluation.html',
		controller: 'projectEvaluationController',
		controllerAs: 'evaluation'
	})
  .state('feedback', {
    url: '/feedback',
    templateUrl: 'views/pages/feedbackForm.html',
    controller: 'feedbackController',
    controllerAs: 'fcontrol'
  })


	.state('review',{
		url: '/review',
		templateUrl: 'views/pages/review.html',
		controller: 'tabController',
	})
  .state('question',{
    url: '/question',
    templateUrl: 'views/pages/questionForm.html',
    controller: 'questionController',
    controllerAs: 'qcontrol'
  })

  	.state('eval', {
    url: '/evaluation',
    templateUrl: 'views/pages/peerEvaluation.html',
    controller: 'evalController',
    controllerAs: 'econtrol'
  })

    .state('events', {
        url: '/events',
        templateUrl:'/views/pages/events.html',
        controller: 'eventController',
        controllerAs: 'event'
    })
		.state('tutorials', {
        url: '/tutorials',
        templateUrl:'/views/pages/tutorials.html',
        controller: 'tutorialController',
        controllerAs: 'tutorial'
    })
		.state('references', {
        url: '/references',
        templateUrl:'/views/pages/references.html',
        controller: 'referenceController',
        controllerAs: 'reference'
    })

	.state('evaluationsDisplay', {
        url: '/evaluationsDisplay',
        templateUrl: '/views/pages/evaluationsDisplay.html',
        controller: 'evaluationsDisplayController',
        controllerAs: 'user'
    })
	
	
    .state('createevent', {
        url: '/events/create',
        templateUrl: '/views/pages/createevent.html',
        controller: 'eventCreateController',
        controllerAs: 'event'
    });


  ;


		$locationProvider.html5Mode(true);
	});
