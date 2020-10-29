// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("千年绿毛龟[2;37;0m[2;37;0m", ({"laogui"}));        
        set("gender", "男性");                
        set("long", "千年绿毛龟[2;37;0m
它是慕容月的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "shiyue");
        set("owner_name", "慕容月");
        set_temp("owner", "shiyue");
        set_temp("owner_name", "慕容月");
        ::setup();
}
