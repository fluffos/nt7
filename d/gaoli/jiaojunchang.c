// /d/gaoli/jiaojunchang
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "较军场");
        set("long", @LONG
这是一座较军场，空旷旷的一个人也没有，只有风吹着落叶，打仗
出兵都从这聚集军队，秋天的官兵比试也在这进行，远处的大台是皇上
的御看台。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northeast":__DIR__"dadao8",  
                 "southwest":__DIR__"dadao7",   
        ]));
       setup();
        
}        
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","jjc");
  return ::valid_leave(ob,dir);
}
