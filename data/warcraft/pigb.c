// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m和谐神兽[2;37;0m[2;37;0m", ({"pigbb"}));        
        set("gender", "男性");                
        set("long", "一切和谐为主，哪怕舍弃国家利益也没关系。。。[2;37;0m
它是胡紧韬的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pigb");
        set("owner_name", "胡紧韬");
        set_temp("owner", "pigb");
        set_temp("owner_name", "胡紧韬");
        ::setup();
}
