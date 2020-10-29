// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m输出文字中[2;37;0m[2;37;0m", ({"bmw"}));        
        set("gender", "男性");                
        set("long", "bmw[2;37;0m
它是刀光血影的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xblade");
        set("owner_name", "刀光血影");
        set_temp("owner", "xblade");
        set_temp("owner_name", "刀光血影");
        ::setup();
}
