inherit ROOM;

void create()
{
        set("short", "过道");
        set("long", @LONG
这里是一条宽敞的过道，用青砖铺就的地面非常整洁，两旁
是汉白玉的雕花栏杆，分外的华贵，每隔几步就有一个仆人打扮
的青年侍立两旁，看起来都身具武功，绝非等闲之辈。置身于此，
让人感觉到莫名的压力。西面不远是一间红砖房，门口还有四条
大汉在把守。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "northeast" : __DIR__"gd6",
  "west" : __DIR__"shufang",
]));

        set("outdoors", "yaowang");
        setup();
}

int valid_leave(object ob,string dir)
{
        if( !wizardp(ob)
        && (dir == "west")
         && (query("family/family_name", ob) != "药王谷") )
                return notify_fail("边上两个药童拦住了你的去路。\n");

        return ::valid_leave(ob,dir);
}
