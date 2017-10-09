var is_regexp = (window.RegExp) ? true : false;

var DOM_type = '';
if (document.getElementById)
{
	DOM_type = "std";
}
else if (document.all)
{
	DOM_type = "ie4";
}
else if (document.layers)
{
	DOM_type = "ns4";
}

var DOM_objects = new Array();

function fetch_object(idname, forcefetch)
{
	if (forcefetch || typeof(DOM_objects[idname]) == "undefined")
	{
		switch (DOM_type)
		{
			case "std":
			{
				DOM_objects[idname] = document.getElementById(idname);
			}
			break;
			
			case "ie4":
			{
				DOM_objects[idname] = document.all[idname];
			}
			break;

			case "ns4":
			{
				DOM_objects[idname] = document.layers[idname];
			}
			break;
		}
	}
	return DOM_objects[idname];
}

function toggle_collapse(objid)
{
	if (!is_regexp)
	{
		return false;
	}
	
	obj = fetch_object("collapseobj_" + objid);	
	img = fetch_object("collapseimg_" + objid);
	
	if (!obj)
	{
		if (img)
		{
			img.style.display = "none";
		}
		return false;
	}

	if (obj.style.display == "none")
	{
		obj.style.display = "";
		if (img)
		{
			img_re = new RegExp("_collapsed\\.gif$");
			img.src = img.src.replace(img_re, '.gif');
		}
	}
	else
	{
		obj.style.display = "none";
		if (img)
		{
			img_re = new RegExp("\\.gif$");
			img.src = img.src.replace(img_re, '_collapsed.gif');
		}
	}
	return false;
}