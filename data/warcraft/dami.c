// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("禁止[2;37;0m[2;37;0m", ({"damid"}));        
        set("gender", "女性");                
        set("long", "禁止[2;37;0m
它是大肚子的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dami");
        set("owner_name", "大肚子");
        set_temp("owner", "dami");
        set_temp("owner_name", "大肚子");
        ::setup();
}
