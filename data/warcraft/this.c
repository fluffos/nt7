// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("丹但[2;37;0m[2;37;0m", ({"dandd"}));        
        set("gender", "女性");                
        set("long", "丹[2;37;0m
它是这个的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "this");
        set("owner_name", "这个");
        set_temp("owner", "this");
        set_temp("owner_name", "这个");
        ::setup();
}
