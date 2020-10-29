// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小宝贝[2;37;0m[2;37;0m", ({"baby"}));        
        set("gender", "男性");                
        set("long", "小宝贝[2;37;0m
它是宝贝熊熊的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ruby");
        set("owner_name", "宝贝熊熊");
        set_temp("owner", "ruby");
        set_temp("owner_name", "宝贝熊熊");
        ::setup();
}
