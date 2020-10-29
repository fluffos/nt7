// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m小青蛇[2;37;0m[2;37;0m", ({"xiaoqing"}));        
        set("gender", "女性");                
        set("long", "一条小蛇而已。[2;37;0m
它是护舒宝的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hushubao");
        set("owner_name", "护舒宝");
        set_temp("owner", "hushubao");
        set_temp("owner_name", "护舒宝");
        ::setup();
}
