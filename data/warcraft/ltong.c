// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("美美[2;37;0m[2;37;0m", ({"rui"}));        
        set("gender", "女性");                
        set("long", "萌萌哒[2;37;0m
它是李千树的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ltong");
        set("owner_name", "李千树");
        set_temp("owner", "ltong");
        set_temp("owner_name", "李千树");
        ::setup();
}
