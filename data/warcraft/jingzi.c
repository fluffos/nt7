// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m乱子[2;37;0m[2;37;0m", ({"luanzi"}));        
        set("gender", "女性");                
        set("long", "小茜的表妹乱子[2;37;0m
它是米青子的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jingzi");
        set("owner_name", "米青子");
        set_temp("owner", "jingzi");
        set_temp("owner_name", "米青子");
        ::setup();
}
