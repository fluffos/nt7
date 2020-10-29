// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit BOOK;

void create()
{
        set_name(HIR"天魔诀"NOR, ({ "tianmo jue", "book" }));
        set_weight(600);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long",HIR"天    魔    诀。\n"NOR);
                set("value", 200);
                set("material", "paper");
                set("skill", ([
                        "name":         "tianmo-jue",           // name of the skill
                        "exp_required": 0,                      // minimum combat experience required
                                                                // to learn this skill.
                        "jing_cost":    20 + random(30),          // jing cost every time study this
                        "difficulty":   25,                     // the base int to learn this skill
                                                                // modify is jing_cost's (difficulty - int)*5%
                        "max_skill":    100                     // the maximum level you can learn
                                                                // from this object.
                ]) );
        }
}

