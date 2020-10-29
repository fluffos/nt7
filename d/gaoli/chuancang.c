// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "船舱");
        set("long", @LONG        
这里是战船的船舱。这里现在没有什么人。桌子上放着一杯茶，还
有些温热，看来这里的人刚出去不久。旁边还有一张图纸，似乎是关于
海战部署的图纸。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "out" : __DIR__"jiaban",
                //"enter":__DIR__"chuancang",
        ]));
       setup();
        
}        
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","zhanchuan");
  return ::valid_leave(ob,dir);
}
