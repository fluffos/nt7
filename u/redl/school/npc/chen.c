// This program is a part of NITAN MudLIB 
// redl 2013/8

#include <ansi.h>
inherit NPC;

void create()
{
        set_name(NOR "陳肥" NOR, ({ "chen fei", "chen" }));
                set("nickname", CYN "看门大叔" NOR);
        set("long", @LONG
这是一个在学校里看门的大叔，尽忠职守，谨慎无过。
LONG);
        set("gender", "男性" );
        set("age", 36);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("per", 13);
        set("combat_exp", 1333000);

        set("inquiry", ([
                "入学" : "问我一个看门的干嘛？你到教室里直接付钱给老师就行。\n"+NOR,
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

}




