// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "渔村");
        set("long", @LONG
这是高丽的一个渔村，这里的人都靠打鱼为生，海岸边停满了渔船。
渔夫们正挑着大担大担的鱼走着，箩里的鱼还在鲜蹦活跳。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northeast" : __DIR__"jiangkou",
                "east" : __DIR__"haigang",
                "southeast" : __DIR__"yuchuan",
        ]));
       setup();
        
}        
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","yucun");
  return ::valid_leave(ob,dir);
}
