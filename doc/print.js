function addToc(num)
{
  var str = "";
  for (var x = 0; x < 10; x++)
    str += ". . ";
  return str + num;
}

function addTocG()
{
  var elems = document.getElementsByTagName("a");

  for (var i = 0; i < elems.length; i++)
  {
    var elem = elems[i];

    if (elem.className == "toc")
    {
      var dots  = document.createElement("span");
      var num   = document.createElement("a");

      dots.className  = "tocDots";
      num.className   = "tocNum";
      num.setAttribute("href", elem.getAttribute("href"));

      elem.parentNode.appendChild(dots);
      elem.parentNode.appendChild(num);
    }
  }

  return "";
}


