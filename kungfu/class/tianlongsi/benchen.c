// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// benchen.c

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("本尘", ({ "ben chen","chen"}) );
        set("gender", "男性" );
        set("long", "他就是天南为帝的大理保定帝段正明。大理历代国主均逊位
天龙寺出家为僧，保定帝亦不例外。\n" );
        set("title", "天龙寺第十七代僧人");
        set("class", "bonze");
        set("age", 45);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 100);
        set("level", 20);
        set("combat_exp", 800000);
        set("score", 1000000);

        set_skill("force", 220);
        set_skill("dodge", 210);
        set_skill("parry", 210);
        set_skill("finger", 220);
        set_skill("sword", 210);
        set_skill("tiannan-bu", 210);
        set_skill("kurong-changong", 220);
        set_skill("duanjia-jian", 210);
        set_skill("sun-finger", 220);
        set_skill("buddhism", 140);
        set_skill("literate", 60);
        set_skill("martial-cognize", 200); 

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("parry", "sun-finger");
        map_skill("finger", "sun-finger");
        map_skill("sword", "duanjia-jian");
        prepare_skill("finger","sun-finger");
        create_family("大理段家", 15, "高僧");
        
        set("inquiry" ,([
                "六脉神剑谱" : "哼！\n",
                "六脉神剑" :  "哼！\n",
        ]));
        
        setup();
        carry_object("/d/xueshan/obj/b-jiasha")->wear();
}
#include "ben.h"
