// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("虎[2;37;0m[2;37;0m", ({"huhu"}));        
        set("gender", "女性");                
        set("long", "白色[2;37;0m
它是秀秀冷的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xiuxiu");
        set("owner_name", "秀秀冷");
        set_temp("owner", "xiuxiu");
        set_temp("owner_name", "秀秀冷");
        ::setup();
}
