// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m阿莱克斯塔萨[2;37;0m[2;37;0m", ({"wxx"}));        
        set("gender", "女性");                
        set("long", "武小虚座下神兽红龙女王阿莱克斯塔萨[2;37;0m
它是武小虚的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wuxiaoxu");
        set("owner_name", "武小虚");
        set_temp("owner", "wuxiaoxu");
        set_temp("owner_name", "武小虚");
        ::setup();
}
