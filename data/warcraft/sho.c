// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "女性");                
        set("long", "就是没有毛！[2;37;0m
它是兽人的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "sho");
        set("owner_name", "兽人");
        set_temp("owner", "sho");
        set_temp("owner_name", "兽人");
        ::setup();
}
