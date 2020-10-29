// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m怜星[2;37;0m[2;37;0m", ({"moonstar"}));        
        set("gender", "男性");                
        set("long", "hello[2;37;0m
它是邀月的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yaoyue");
        set("owner_name", "邀月");
        set_temp("owner", "yaoyue");
        set_temp("owner_name", "邀月");
        ::setup();
}
