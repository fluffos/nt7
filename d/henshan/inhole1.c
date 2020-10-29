inherit ROOM;

void create()
{
        set("short", "水帘洞内");
        set("long", @LONG
这里是水莲洞内洞，虽然不如外洞高，但也甚为宽敞，此处靠近
外洞还隐隐地听得见瀑布落下拍打在石头上的声音。走到这里入口便
一分为二，出现两个洞口。从这里看去洞口漆黑无光，令人不禁有些
心寒。
LONG );

        set("exits",([
              "northwest" : __DIR__"inhole2",
              "northeast" : __DIR__"inhole3",                
              "out"       : __DIR__"inhole",              
        ]));        
                     
       setup();
       replace_program(ROOM);
}