// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("模压[2;37;0m[2;37;0m", ({"bai"}));        
        set("gender", "女性");                
        set("long", "模压[2;37;0m
它是普诵白姓的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "baixing");
        set("owner_name", "普诵白姓");
        set_temp("owner", "baixing");
        set_temp("owner_name", "普诵白姓");
        ::setup();
}
