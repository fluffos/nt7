// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "寺院");
        set("long", @LONG        
这里是一座寺院，抬头可以看到一个大匾，上面写着：灵静寺。这
是中原的僧人在这里掌管的寺院，以在高丽宣扬佛法。里面传来了阵阵
的诵佛之声，声音悠扬久远，经久不息。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"caodi1",
                "enter":__DIR__"baodian",
               ]));
       set("objects",([
         __DIR__"npc/sengren":1,
         ]));
       setup();
        replace_program(ROOM);
}        
