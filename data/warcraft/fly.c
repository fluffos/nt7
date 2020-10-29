// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"niao"}));        
        set("gender", "女性");                
        set("long", "你中奖了.[2;37;0m
它是落花吹雪的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fly");
        set("owner_name", "落花吹雪");
        set_temp("owner", "fly");
        set_temp("owner_name", "落花吹雪");
        ::setup();
}
