// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "大雄宝殿");
        set("long", @LONG        
这里是灵静寺的大雄宝殿。有几个僧人正在这里诵经念佛。这里香
气缭绕，一派庄严的气氛。有几个人正在这里跪拜佛祖，口中念念有词，
不知是在祈祷平安还是在祈祷福运。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "out" : __DIR__"miaodoor",
                      ]));
       setup();
        
}        
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","simiao");
  return ::valid_leave(ob,dir);
}
