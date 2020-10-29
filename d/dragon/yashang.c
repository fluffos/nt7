inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "叠嶂峰");
        set("long",
"[1;32m这里群峰叠嶂，都是一根而出，看似群峰，也难说清究竟该\n"
"有多少。然而，山峰虽众，却唯此一峰独尊。一株奇异的小草长在山峰绝\n"
"高之处，瑞气祥云皆由此而来。\n"
);
        set("exits", ([ 
             "down" : __DIR__"mountain",
]));
        set("objects", ([ 
        "/quest/tulong/obj/drug1" : 1,
        "/quest/tulong/npc/spirit2" : 1,
                        ]) );
        set("no_magic", 1);
        setup();
//      replace_program(ROOM);
}

void grass_grow()
{
        object grass;
        seteuid(getuid());
        if(grass=new("/quest/tulong/obj/drug1")){
                grass->move(this_object());
                grass->invocation();
        }
        return;
}
