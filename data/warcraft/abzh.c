// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m呆[1;37m瓜[2;37;0m[2;37;0m", ({"abzhh"}));        
        set("gender", "女性");                
        set("long", "随时会便[2;37;0m
它是呆子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "abzh");
        set("owner_name", "呆子");
        set_temp("owner", "abzh");
        set_temp("owner_name", "呆子");
        ::setup();
}
