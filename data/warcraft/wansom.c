// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m小龙女[2;37;0m[2;37;0m", ({"ook"}));        
        set("gender", "女性");                
        set("long", "美若天仙的贤惠小龙女[2;37;0m
它是款矿神的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wansom");
        set("owner_name", "款矿神");
        set_temp("owner", "wansom");
        set_temp("owner_name", "款矿神");
        ::setup();
}
