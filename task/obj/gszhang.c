#include <ansi.h>
inherit TASK;
void create()
{
    set_name("怪蛇杖", ({ "guaishe zhang", "shezhang", "zhang"}));
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "根");
            set("material", "wood");
            set("long", "一根顶部有条怪蛇的蛇杖，蛇头处有机关，咬起人来厉害无比！\n");
          }
    set("owner", "欧阳锋");
    setup();
}
