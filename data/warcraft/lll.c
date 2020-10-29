// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("战斗机[2;37;0m[2;37;0m", ({"hhh"}));        
        set("gender", "女性");                
        set("long", "战斗机[2;37;0m
它是柳六的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lll");
        set("owner_name", "柳六");
        set_temp("owner", "lll");
        set_temp("owner_name", "柳六");
        ::setup();
}
