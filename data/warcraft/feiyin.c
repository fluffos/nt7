// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("雁[2;37;0m[2;37;0m", ({"yinyin"}));        
        set("gender", "女性");                
        set("long", "飞飞飞[2;37;0m
它是飞燕的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "feiyin");
        set("owner_name", "飞燕");
        set_temp("owner", "feiyin");
        set_temp("owner_name", "飞燕");
        ::setup();
}
