// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m天青朱雀[2;37;0m[2;37;0m", ({"dfengpet"}));        
        set("gender", "男性");                
        set("long", "一只幼小的天青朱雀！[2;37;0m
它是段风的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dfeng");
        set("owner_name", "段风");
        set_temp("owner", "dfeng");
        set_temp("owner_name", "段风");
        ::setup();
}
