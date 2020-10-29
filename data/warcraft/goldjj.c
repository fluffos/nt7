// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("鸡[2;37;0m[2;37;0m", ({"goldjjj"}));        
        set("gender", "男性");                
        set("long", "鸡[2;37;0m
它是金鸡的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldjj");
        set("owner_name", "金鸡");
        set_temp("owner", "goldjj");
        set_temp("owner_name", "金鸡");
        ::setup();
}
