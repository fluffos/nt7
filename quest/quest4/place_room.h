mapping area=([
"西城" : ({"/maze/jingcheng/","dadao36","dadao35","dadao34","dadao33","dadao32",
         "dadao31","dadao30","dadao29","dadao28","dadao27","dadao26","dadao25",
         "dadao24","dadao23","dadao22","dadao21","dadao20","dadao19","dadao18",
         "dadao17","dadao16","dadao15","dadao14","dadao13","dadao12","dadao11",
         "dadao10","dadao9","dadao8","dadao7"
          }),
"东城" : ({"/maze/jingcheng/","dao1","dao2","dao3","dao4","dao5",
         "dao6","dao7","dao8","dao9","dao10","dao11","dao12",
         "dao13","dao14","dao15","dao16","dao17","dao18","dao19",
         "dao20","dao21","dao22","dao23","dao24","dao25","dao26",
         "dao27","dao28","dao29","dao30"
          })
]);

int place_room(string site_name,object ob)
{
        string *location, site_file;
        int size;

        location=area[site_name];
        size=sizeof(location);
        site_file=location[0]+location[random(size-1)+1];
        set("area",site_name, ob);
        set("place_name",site_file,ob);
        ob->move(site_file);
        return 1;
}
