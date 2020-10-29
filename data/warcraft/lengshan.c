// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("衣衫[2;37;0m[2;37;0m", ({"yishan"}));        
        set("gender", "男性");                
        set("long", "衣衫[2;37;0m
它是冷杉的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lengshan");
        set("owner_name", "冷杉");
        set_temp("owner", "lengshan");
        set_temp("owner_name", "冷杉");
        ::setup();
}
