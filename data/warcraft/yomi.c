// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m乱红莲[2;37;0m[2;37;0m", ({"nue"}));        
        set("gender", "女性");                
        set("long", "这是一只有着许多眼睛红色狮子，尾巴变成了许多条响尾蛇。[2;37;0m
它是谏山黄泉的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yomi");
        set("owner_name", "谏山黄泉");
        set_temp("owner", "yomi");
        set_temp("owner_name", "谏山黄泉");
        ::setup();
}
