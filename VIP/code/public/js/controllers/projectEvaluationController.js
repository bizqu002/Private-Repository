angular.module('projectEvaluationControl', ['projectEvaluationService', 'userService', 'mailService'])

    // controller applied to user creation page
    .controller('projectEvaluationController', function(Evaluations, User, Mail) {

        var vm = this;
        vm.title = "Project Evaluation";

        // grab all the users at page load
        // "User" refers to userService factory object
        User.all()
            .success(function(data) {
                // when all the users come back, remove the processing variable
                vm.processing = false;
                // bind the users that come back to vm.users
                vm.users = data;
            });

        // function to create a user
        vm.saveEvaluation = function() {
            vm.processing = true;
            vm.message = '';

            //to send an Email to student user
            vm.emailData = {};
            var student = vm.feedback.student;
            var start = student.indexOf("<");
            var end = student.indexOf(">");
            vm.emailData.recipient = student.substring(start+1, end);
            vm.emailData.sender = 'Professor <fiu-vip@fiu.edu>';
            vm.emailData.subject = 'Project Evaluation';
            var studentName = student.substring(0, start -1);
            vm.emailData.message = 'Dear ' + studentName + ',\n\nYou have received the following feedback on your evaluation:\n\n' + vm.feedback.feedbackMessage;

            //for the Evaluation model
            vm.feedback.student = studentName;
            vm.feedback.email = vm.emailData.recipient;
            vm.feedback.subjectTitle = vm.emailData.subject;
            vm.feedback.feedbackMessage = vm.emailData.message;

            // use the create function
            Evaluations.create(vm.feedback)
                .success(function(data) {
                    vm.processing = false;
                    vm.feedback = {};
                    vm.message = data.message;
                    Mail.sendEmail(vm.emailData)
                        .success(function(data) {
                            console.log("Successful send!");
                        })
                });
        };


    });