// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("凤凰[2;37;0m[2;37;0m", ({"qlw"}));        
        set("gender", "男性");                
        set("long", "凤凰[2;37;0m
它是无际的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kokob");
        set("owner_name", "无际");
        set_temp("owner", "kokob");
        set_temp("owner_name", "无际");
        ::setup();
}
