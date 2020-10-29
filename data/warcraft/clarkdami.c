// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("十米虎[2;37;0m[2;37;0m", ({"damishou"}));        
        set("gender", "男性");                
        set("long", "只是一只迷你虎[2;37;0m
它是李十米的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "clarkdami");
        set("owner_name", "李十米");
        set_temp("owner", "clarkdami");
        set_temp("owner_name", "李十米");
        ::setup();
}
