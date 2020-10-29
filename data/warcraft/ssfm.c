// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("凤凰[2;37;0m[2;37;0m", ({"zhuqf"}));        
        set("gender", "女性");                
        set("long", "一只凤凰 [2;37;0m
它是白衣少年的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ssfm");
        set("owner_name", "白衣少年");
        set_temp("owner", "ssfm");
        set_temp("owner_name", "白衣少年");
        ::setup();
}
