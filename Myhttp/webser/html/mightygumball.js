window.onload = function(){
    // port : 9999
    // ip   : 10.0.142.103
    var url = "http://10.0.142.103:9999/html/sales.json";

    var request = new XMLHttpRequest();

  
    request.open("GET",url);
    request.onload = function(){
        
        if(200 == request.status){
            updateSales(request.responseText);
        }
    }
    var salesDiv = document.getElementById("sales");
    salesDiv.innerHTML = request.responseText;
    request.send(null);
}


function updateSales(responseText){
    var salesDiv = document.getElementById("sales");
    salesDiv.innerHTML = responseText;
}


// function HttpGet(){
//     var url = "http://someserver.com/data.json";
//     var request = new XMLHttpRequest();
//     request.open("GET",url);

//     //
//     request.onload = function(){
//         if(request.status==200){
//             alert(request.responseText);
//         }
//     };
//     request.send(null);
//     var plan9Movie = new Movie("Plan 9 from Outer Space",
//                                 "Cult Classic",
//                                 2,["3:00pm","7:00pm","11:00pm"]);
//     var jsonString = JSON.stringify(plan9Movie);
//     alert(jsonString);
//     var jsonMovieObject = JSON.parse(jsonString);
//     alert("JSON Movie is " + jsonMovieObject.title);
// }

// http://search.twitter.com/search.json?q=hfhtml5
// http://gumball.wickedlysmart.com/?lastreporttime=1302212903099