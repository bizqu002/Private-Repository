
# Author: Brenda S. Izquierdo
# PID: 3886796
#

library(shiny)

shinyServer(function(input, output, session) {

  observeEvent(input$open_parenthesis, {
    symbols$counter <- 0
    symbols$temp <- symbols$data
    symbols$temp2 <- symbols$number
    symbols$number <- 0
    symbols$data <- NULL
  })
  
  observeEvent(input$close_parenthesis, {
    symbols$counter <- 0
    button_equal_result()
    symbols$data <- symbols$temp
    symbols$number <- symbols$temp2
  })

  
  observeEvent(input$negative, {
    updateNumericInput(session, "num1", value = input$num1*-1)
  })
  
  observeEvent(input$sine, {
    if(input$radio == 1)
      updateNumericInput(session, "num1", value = sin(input$num1*pi/180))
    else
      updateNumericInput(session, "num1", value = sin(input$num1))
  })
  
  observeEvent(input$cosine, {
    if(input$radio == 1)
      updateNumericInput(session, "num1", value = cos(input$num1*pi/180))
    else
      updateNumericInput(session, "num1", value = cos(input$num1))
  })
  
  observeEvent(input$tangent, {
    if(input$radio == 1)
      updateNumericInput(session, "num1", value = tan(input$num1*pi/180))
    else
      updateNumericInput(session, "num1", value = tan(input$num1))
  })
  
  observeEvent(input$arcsine, {
    if(input$radio == 1)
      updateNumericInput(session, "num1", value = asin(input$num1)*180/pi)
    else
      updateNumericInput(session, "num1", value = asin(input$num1))
  })
  
  observeEvent(input$arccosine, {
    if(input$radio == 1)
      updateNumericInput(session, "num1", value = acos(input$num1)*180/pi)
    else
      updateNumericInput(session, "num1", value = acos(input$num1))
  })
  
  observeEvent(input$arctangent, {
    if(input$radio == 1)
      updateNumericInput(session, "num1", value = atan(input$num1)*180/pi)
    else
      updateNumericInput(session, "num1", value = atan(input$num1))
  })
  
  observeEvent(input$pi, {
    updateNumericInput(session, "num1", value = pi)
  })
  
  observeEvent(input$e, {
    updateNumericInput(session, "num1", value = 2.718281828459045)
  })
  
  observeEvent(input$xtoy, {
    symbols$counter <- 0
    result()
    symbols$data <- "^"
  })
  
  observeEvent(input$xtotwo, {
    updateNumericInput(session, "num1", value = input$num1^2)
  })
  
  observeEvent(input$xtothree, {
    updateNumericInput(session, "num1", value = input$num1^3)
  })
  
  observeEvent(input$etox, {
    updateNumericInput(session, "num1", value = 2.7182818284590452353602874713527^input$num1)
  })
  
  observeEvent(input$tentox, {
    updateNumericInput(session, "num1", value = 10^input$num1)
  })
  
  observeEvent(input$yrootofx, {
    symbols$counter <- 0
    result()
    symbols$data <- "√"
  })
  
  observeEvent(input$cubicrootofx, {
    updateNumericInput(session, "num1", value = input$num1^(1/3))
  })
  
  observeEvent(input$quadraticrootofx, {
    updateNumericInput(session, "num1", value = input$num1^(1/2))
  })
  
  observeEvent(input$ln, {
    updateNumericInput(session, "num1", value = log(input$num1))
  })
  
  observeEvent(input$log, {
    updateNumericInput(session, "num1", value = log10(input$num1))
  })
  
  observeEvent(input$percent, {
    updateNumericInput(session, "num1", value = input$num1/100)
  })
  
  observeEvent(input$factorial, {
    updateNumericInput(session, "num1", value = factorial(input$num1))
  })
  

   observeEvent(input$EXP, {
     symbols$counter <- 0
     result()
     symbols$data <- "E"
  })
  
   observeEvent(input$RND, {
     updateNumericInput(session, "num1", value = runif(1,0,1))
   })
  
  
  observeEvent(input$memory_recall, {
     updateNumericInput(session, "num1", value = symbols$memory)
  })
  
  observeEvent(input$memory_store, {
    symbols$memory <- input$num1 
  })
  
  observeEvent(input$add_to_memory, {
    symbols$memory <- symbols$memory + input$num1
  })
  
  observeEvent(input$subtract_from_memory, {
    symbols$memory <- symbols$memory - input$num1
  })
  
  observeEvent(input$clear_memory, {
    symbols$memory <- 0
  })
  
  observeEvent(input$reset, {
    updateNumericInput(session, "num1", value = 0)
    symbols$data <- NULL
    symbols$counter <- 0
    symbols$number <- 0
  })
  
  observeEvent(input$clear, {
    if(symbols$counter == 0 || symbols$counter == 1)
    {
      if(input$num1 > 0)
         updateNumericInput(session, "num1", value = input$num1%/%10)
      else
      {  
        symbols$temp3 <- (input$num1*-1)%/%10
        updateNumericInput(session, "num1", value = symbols$temp3*-1)
      }
      symbols$counter <- 0
    }
    else if(symbols$counter == -1)
      updateNumericInput(session, "num1", value = input$num1)
    else
    {  
      if(input$num1 > 0)
        updateNumericInput(session, "num1", value = ((input$num1*10^(symbols$counter-1))%/%10)/10^(symbols$counter-2))
      else
      {
        symbols$temp3 <- (((input$num1*-1)*10^(symbols$counter-1))%/%10)/10^(symbols$counter-2)
        updateNumericInput(session, "num1", value = symbols$temp3*-1)
      }
      symbols$counter <- symbols$counter - 1 
    }
    
  })
  
  output$final_result <- eventReactive(input$inverse, {
      paste0("<strong>", "1/", input$num1, " = ", 1/input$num1, "</strong>")
  })
  
  observeEvent(input$inverse, {
      updateNumericInput(session, "num1", value = 1/input$num1)
  })
  
  observeEvent(input$decimal, {
    symbols$counter = 1;
    
  })
  
  observeEvent(input$one, {
    if(symbols$counter == 0)
       updateNumericInput(session, "num1", value = input$num1*10+1)
    else
    {  
       updateNumericInput(session, "num1", value = (input$num1*10^symbols$counter+1)/(10^symbols$counter))
       symbols$counter <- symbols$counter + 1
    }
  })
  
  observeEvent(input$two, {
    if(symbols$counter == 0)
      updateNumericInput(session, "num1", value = input$num1*10+2)
    else
    {  
      updateNumericInput(session, "num1", value = (input$num1*10^symbols$counter+2)/(10^symbols$counter))
      symbols$counter <- symbols$counter + 1
    }
  })
  
  observeEvent(input$three, {
    if(symbols$counter == 0)
      updateNumericInput(session, "num1", value = input$num1*10+3)
    else
    {  
      updateNumericInput(session, "num1", value = (input$num1*10^symbols$counter+3)/(10^symbols$counter))
      symbols$counter <- symbols$counter + 1
    }
  })
  
  observeEvent(input$four, {
    if(symbols$counter == 0)
      updateNumericInput(session, "num1", value = input$num1*10+4)
    else
    {  
      updateNumericInput(session, "num1", value = (input$num1*10^symbols$counter+4)/(10^symbols$counter))
      symbols$counter <- symbols$counter + 1
    }
  })
  
  observeEvent(input$five, {
    if(symbols$counter == 0)
      updateNumericInput(session, "num1", value = input$num1*10+5)
    else
    {  
      updateNumericInput(session, "num1", value = (input$num1*10^symbols$counter+5)/(10^symbols$counter))
      symbols$counter <- symbols$counter + 1
    }
  })
  
  observeEvent(input$six, {
    if(symbols$counter == 0)
      updateNumericInput(session, "num1", value = input$num1*10+6)
    else
    {  
      updateNumericInput(session, "num1", value = (input$num1*10^symbols$counter+6)/(10^symbols$counter))
      symbols$counter <- symbols$counter + 1
    }
  })
  
  observeEvent(input$seven, {
    if(symbols$counter == 0)
      updateNumericInput(session, "num1", value = input$num1*10+7)
    else
    {  
      updateNumericInput(session, "num1", value = (input$num1*10^symbols$counter+7)/(10^symbols$counter))
      symbols$counter <- symbols$counter + 1
    }
  })
  
  observeEvent(input$eight, {
    if(symbols$counter == 0)
      updateNumericInput(session, "num1", value = input$num1*10+8)
    else
    {  
      updateNumericInput(session, "num1", value = (input$num1*10^symbols$counter+8)/(10^symbols$counter))
      symbols$counter <- symbols$counter + 1
    }
  })
  
  observeEvent(input$nine, {
    if(symbols$counter == 0)
      updateNumericInput(session, "num1", value = input$num1*10+9)
    else
    {  
      updateNumericInput(session, "num1", value = (input$num1*10^symbols$counter+9)/(10^symbols$counter))
      symbols$counter <- symbols$counter + 1
    }
  })
  
  observeEvent(input$zero, {
    if(symbols$counter == 0)
      updateNumericInput(session, "num1", value = input$num1*10)
    else
    {  
      updateNumericInput(session, "num1", value = (input$num1*10^symbols$counter)/(10^symbols$counter))
      symbols$counter <- symbols$counter + 1
    }
  })
  
  output$plus <- renderUI({actionButton("addition", label = "+", style="color: #fff; background-color: #ff7f50; border-color: #2e6da4")})
  output$minus <- renderUI({actionButton("subtraction", label = "-", style="color: #fff; background-color: #ff7f50; border-color: #2e6da4")})
  output$asterisk <- renderUI({actionButton("multiplication", label = "*", style="color: #fff; background-color: #ff7f50; border-color: #2e6da4")})
  output$dash <- renderUI({actionButton("division", label = "÷", style="color: #fff; background-color: #ff7f50; border-color: #2e6da4")})
  
  symbols <- reactiveValues(data = NULL, number = 0, counter = 0, memory = 0, temp = NULL, temp2 = 0, temp3 = 0)
  
  result <- reactive({
    
    if(is.null(symbols$data))
       symbols$number <- input$num1
    else if(!is.null(symbols$data) && symbols$data == "+")
       symbols$number <- symbols$number + input$num1
    else if(!is.null(symbols$data) && symbols$data == "-")
      symbols$number <- symbols$number - input$num1
    else if(!is.null(symbols$data) && symbols$data == "*")
      symbols$number <- symbols$number * input$num1
    else if(!is.null(symbols$data) && symbols$data == "÷")
      symbols$number <- symbols$number / input$num1
    else if(!is.null(symbols$data) && symbols$data == "^")
      symbols$number <- symbols$number ^ input$num1
    else if(!is.null(symbols$data) && symbols$data == "√")
      symbols$number <- symbols$number ^ (1/input$num1)
    else if(!is.null(symbols$data) && symbols$data == "E")
      symbols$number <- symbols$number*10^input$num1
    updateNumericInput(session, "num1", value = 0)
  })
  
  observeEvent(input$addition, {
    
    symbols$counter <- 0
    result()
    symbols$data <- "+"
    
  })
  
  observeEvent(input$subtraction, {
    
    symbols$counter <- 0
    result()
    symbols$data <- "-"
  })  
  
  observeEvent(input$multiplication, {
    symbols$counter <- 0
    result()
    symbols$data <- "*"
  })  
  
  observeEvent(input$division, {
    symbols$counter <- 0
    result()
    symbols$data <- "÷"
  }) 
  
  output$operand1 <- renderText({ 
    if (is.null(symbols$data)) return()
    symbols$data
  })

  
  button_equal_result <- reactive({
    symbols$counter <- -1
     if(is.null(symbols$data)) #in case user clicks equal without having made a previous operation
      updateNumericInput(session, "num1", value = input$num1)
    else if(symbols$data == "+")
      updateNumericInput(session, "num1", value = symbols$number + input$num1)
    else if(symbols$data == "-")
      updateNumericInput(session, "num1", value = symbols$number - input$num1)  
    else if(symbols$data == "*")
      updateNumericInput(session, "num1", value = symbols$number * input$num1)
    else if(symbols$data == "÷")
      updateNumericInput(session, "num1", value = symbols$number / input$num1)
    else if(symbols$data == "^")
      updateNumericInput(session, "num1", value = symbols$number ^ input$num1)
    else if(symbols$data == "√")
      updateNumericInput(session, "num1", value = symbols$number ^ (1/input$num1))
    else if(symbols$data == "E")
      updateNumericInput(session, "num1", value = symbols$number*10^input$num1)
    symbols$data <- NULL
    symbols$number <- 0
    
  })
  observeEvent(input$equal, {
   
    button_equal_result()
    
  })

 
})