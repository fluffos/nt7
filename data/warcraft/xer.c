// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "这是一只白色的老虎[2;37;0m
它是北城雪的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xer");
        set("owner_name", "北城雪");
        set_temp("owner", "xer");
        set_temp("owner_name", "北城雪");
        ::setup();
}
