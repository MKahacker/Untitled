var divs = $('.slide_show_content');
$(window).scroll(function(){
   if($(window).scrollTop()<10){
         divs.stop(true,true).fadeIn("fast");
   } else {
         divs.stop(true,true).fadeOut("fast");
   }
});