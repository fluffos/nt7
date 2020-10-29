// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m小红雕[2;37;0m[2;37;0m", ({"diao"}));        
        set("gender", "女性");                
        set("long", "四圣兽中防御最高的玄武[2;37;0m
它是黄蓉的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "warrierc");
        set("owner_name", "黄蓉");
        set_temp("owner", "warrierc");
        set_temp("owner_name", "黄蓉");
        ::setup();
}
