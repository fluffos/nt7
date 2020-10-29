// 客栈类工作守护：kezhan.c

// Updated by Lonely



// 获准工作(老板)

//     |

// 分配工作(小二) -+- 扫地 ----+

//                 |           +-- 工作过程 -- 完成 +

//                 +- 洗盘子 --+                    |

//                                 领取奖励(小二) --+



#include <ansi.h>



#define NAME            "kezhan"        // 工作名称

#define BONUS           10 + random(30) // 奖励基数

#define MAX_NUM         20              // 最多人数，为 0 时不检查

#define MIN_EXP         0               // 最少经验

#define MAX_EXP         100000          // 最多经验，为 0 时不检查



// 提供的外部函数

public int    query_work(object me);

public int    request_work(object me, object ob);

public int    start_work(object me);

public int    finish_work(object me, object ob, object obj);

public string assign_work(object me);



// 工作对象创建

void create() { seteuid(getuid()); }



private int fail_msg(string arg) 

{ 

        write(arg);

        return 1; 

}



private string query_zone(object arg)

{

        string zone;

        

        if (sscanf(file_name(arg), "/d/%s/%*s", zone) == 2)

                return zone;

        return "work";

}



// 查询 me 的任务状态

public int query_work(object me) { return me->query_temp("work/" + NAME + "/state"); }



// 请求任务，me 为请求者，ob 为被请求者

public int request_work(object me, object ob)

{

        // 分派工作者的检查

        if (playerp(ob) || ob->query("work/name") != NAME)

                return fail_msg(ob->name() + "望着你呵呵傻笑。\n");



        if (MAX_NUM > 0 && ob->query("work/working") >= MAX_NUM)

                return fail_msg(ob->name() + "一皱眉道：“现在我们"

                                "这里不缺人手，你等人少的时候再来吧"

                                "。”\n");

        // 接受工作者的检查

        if (ob->query("combat_exp") < MIN_EXP)

                return fail_msg(ob->name() + "瞥了" + me->name() +

                                "一眼道：“就凭你也干得了咱这工作？"

                                "”\n");

        if (MAX_EXP > 0 && me->query("combat_exp") > MAX_EXP && ! wizardp(me))

                return fail_msg(ob->name() + "满脸堆笑道：“这点小"

                                "事就不敢麻烦大侠您了。”\n");



        switch(query_work(me))

        {

        // 0 为不在做此工作

        case 0:

                message_vision(CYN "$N" NOR CYN "一点头对$n" NOR CYN 

                               "道：“嗯，好吧，你去厨房看看有什么工作"

                               "可做的。”\n", ob, me);

                // 设定玩家做此工作的状态

                me->set_temp("work/" + NAME + "/state", 1);

                me->set_temp("work/" + NAME + "/zone", query_zone(environment(ob)));



                break;

        // 1 为许可了，尚未正式开始工作

        case 1:

                message_vision(CYN "$N" NOR CYN "疑惑的对$n" NOR CYN

                               "道：“咦，你不是已经领了工作么？还不快"

                               "去？”\n", ob, me);

                break;

        // 2 为正在进行工作

        case 2:

                message_vision(CYN "$N" NOR CYN "皱着眉头对$n" NOR CYN

                               "道：“你不是正在做事嘛？快回去，做完再"

                               "来我这领奖励。”\n", ob, me);

                break;

        // 3 为工作过程已经完成，正获取奖励

        case 3:

                message_vision(CYN "$N" NOR CYN "用毛巾抹了抹手，对$n"

                               NOR CYN "道：“掌柜的，我的事儿做完了，"

                               "您......”\n", me, ob);

                finish_work(me, ob, 0);

                break;

        default:

                return 0;

        }

        return 1;

}



// 按照状态分配一个具体的工作分支，并返回这个工作分支的描述信息

public string assign_work(object me)

{

        string msg;

        int i;

        object dish, besom;



        switch (random(2))

        {

        // 洗盘子

        case 0:

                i = 2 + random(3);

                dish = new("/clone/work/dish");

                dish->set_amount(i);

                dish->move(me);

                msg = "喏，这里有" + chinese_number(i) + "个盘子(dish)，"

                      "快帮我洗洗(wash)，急着用呢。";

                me->set_temp("work/" + NAME + "/type", "wash");

                me->set_temp("work/" + NAME + "/wash", i);

                break;

        // 扫地

        case 1:

                besom = new("/clone/work/besom");

                besom->move(me);

                msg = "唔，这里的地(floor)也够脏的了，你把这里四周给扫扫"

                      "(sweep)，手脚麻利些。";

                me->set_temp("work/" + NAME + "/type", "sweep");

                break;

        }

        me->set_temp("work/" + NAME + "/state", 2);

        return msg;

}



// 开始工作，根据玩家身上的设定决定工作类型

public int start_work(object me)

{

        string type;

        object ob;

        array place;



        if (! mapp(me->query_temp("work/" + NAME)))

                return fail_msg("你现在并没有领到工作呀，瞎折腾个啥呢"

                                "。\n");

        

        if (! stringp(type = me->query_temp("work/" + NAME + "/type")) ||

            type != "wash" && type != "sweep")

                return fail_msg("似乎什么地方出了一点问题，你并没有被"

                                "分配到具体的工作类型。\n");



        if (me->is_busy())

                return fail_msg("你忙完手里的事情再工作吧。\n");



        switch (type)

        {

        case "wash":

                if (! objectp(ob = present("dirty dish", me)))

                        return fail_msg("你的身上已经没有脏盘子了。\n");



                if (! environment(me)->query("resource/water"))

                        return fail_msg("这里没有水，怎么洗呢？\n");



                if (me->query("qi") < 30 || me->query("eff_qi") < 50 ||

                    me->query("jing") < 20 || me->query("eff_jing") < 50)

                        return fail_msg("你先歇歇再洗吧，可别洗盘子洗出"

                                        "人命来。\n");



                me->set_temp("work/" + NAME + "/step", 1);

                me->start_busy(bind((: call_other, __FILE__, "continue_working" :), me),

                               bind((: call_other, __FILE__, "halt_working" :), me));



                tell_object(me, "你开始工作。\n");

                return 1;

                

        case "sweep":

                if (! objectp(ob = present("besom", me)))

                        return fail_msg("你的身上都没有扫把，怎么扫？\n");



                // 只能在客栈扫地

                if (! environment(me)->query("hotel") ||

                    me->query_temp("work/" + NAME + "/zone") != query_zone(environment(me)))

                        return fail_msg("这里可不是店小二叫你扫的地方呀。\n");



                if (arrayp(place = me->query_temp("work/" + NAME + "/place")) &&

                    member_array(file_name(environment(me)), place) != -1)

                        return fail_msg("这个地方你已经扫过了，不必再重复一次。\n");



                if (me->query("qi") < 30 || me->query("eff_qi") < 30 ||

                    me->query("jing") < 20 || me->query("eff_jing") < 30)

                        return fail_msg("你先歇歇再扫吧，可别扫地洗出人命来。\n");



                me->set_temp("work/" + NAME + "/step", 1);

                me->start_busy(bind((: call_other, __FILE__, "continue_working" :), me),

                               bind((: call_other, __FILE__, "halt_working" :), me));



                tell_object(me, "你开始工作。\n");

                return 1;

        }

        return 0;

}



// 正在工作

int continue_working(object me)

{

        string msg;

        int finish;

        int b;



        if (! me->query_temp("work/" + NAME + "/step"))

                me->set_temp("work/" + NAME + "/step", 1);



        if (! living(me))

        {

                me->delete_temp("work/" + NAME + "/step");

                return 0;

        }



        finish = 0;

        me->receive_damage("jing", 1);

        me->receive_damage("qi", 2);

        

        switch (me->query_temp("work/" + NAME + "/type"))

        {

        case "wash":

                switch (me->query_temp("work/" + NAME + "/step"))

                {

                case 1:

                        msg = "$N抓起一个脏盘子，浸入水盆。";

                        break;

                case 2:

                        msg = "$N往盆子里倒了一些皂角液。";

                        break;

                case 3:

                        msg = "$N左手捏着盘子，右手拿着抹布，开始擦抹。";

                        break;

                case 4:

                case 6:

                        msg = "$N小心翼翼的擦抹盘子。";

                        break;

                case 5:

                        msg = "$N给抹布蘸了点水，继续仔细地洗盘子。";

                        break;

                case 7:

                        msg = "$N不断擦抹着盘子，盘子上的污垢渐渐除去。";

                        break;

                default:

                        msg = "$N洗好以后，将盘子透干，用抹布一抹，放在旁边晾干。";

                        finish = 1;

                        break;

                }

                break;

        case "sweep":

                switch (me->query_temp("work/" + NAME + "/step"))

                {

                case 1:

                        msg = "$N抓起手边的扫把，戴上袖套。";

                        break;

                case 2:

                        msg = "$N往地上洒了点水。";

                        break;

                case 3:

                        msg = "$N费力的挥动扫把，开始打扫地上的垃圾。";

                        break;

                case 4:

                case 6:

                        msg = "$N埋头清扫地上的灰尘。";

                        break;

                case 5:

                        msg = "$N铲起脚边的垃圾，继续仔细地扫地。";

                        break;

                case 7:

                        msg = "$N不断扫拭着地面，地面渐渐变得光可鉴人。";

                        break;

                default:

                        msg = "$N扫好以后，将所有的垃圾铲进箩筐，放下扫把。";

                        finish = 1;

                        break;

                }

                break;

        }

        msg += "\n";



        if (finish)

        {

                object dish, cdish;



                me->delete_temp("work/" + NAME + "/step");



                b = BONUS;

                // 奖励修正

                if (me->query("combat_exp") > 200000)

                {

                        // 经验太高，削弱奖励

                        b = b / 2 + 1;

                        if (me->query("combat_exp") > 400000)

                        {

                                // 再次削弱奖励

                                b = b / 2 + 1;

                        }

                }

                me->add("combat_exp", b);

                me->improve_potential((b + 2) / 3);



                if (me->query_temp("work/" + NAME + "/type") == "wash")

                {

                        if (objectp(dish = present("dirty dish", me)))

                        {

                                dish->add_amount(-1);

                                me->add_temp("work/" + NAME + "/washed", 1);

                                if (! objectp(cdish = present("clear dish", me)))

                                {

                                        cdish = new("/clone/work/cdish");

                                        cdish->move(me);

                                }

                                else 

                                        cdish->add_amount(1);

                        }

                        // 洗完了所有的盘子

                        if (me->query_temp("work/" + NAME + "/washed") ==

                            me->query_temp("work/" + NAME + "/wash"))

                                me->set_temp("work/" + NAME + "/state", 3);

                        msg += "你洗好了一个干净的盘子。\n";

                }

                else

                {

                        me->add_temp("work/" + NAME + "/place",

                                    ({ file_name(environment(me)) }));

                        me->set_temp("work/" + NAME + "/state", 3);

                        msg += "你把这个地方扫干净了。\n";

                }

        }



        msg = replace_string(msg, "$N", "你");

        tell_object(me, msg);



        if (finish)

        {

                if (b > 0)

                {

                        tell_object(me, HIC "\n你获得了" +

                                    chinese_number(b) +

                                    "点经验和" +

                                    chinese_number((b + 2) / 3) +

                                    "点潜能。\n\n" NOR);

                }

                return 0;

        }



        me->add_temp("work/" + NAME + "/step", 1);

        return 1;

}



// 中途停止工作

int halt_working(object me)

{

        if (me->query_temp("work/" + NAME + "/type") == "wash")

                message_vision("$N把手中的抹布盘子丢到一旁，抹了抹汗道："

                               "太累了太累了，歇歇再干。\n", me);

        else

                message_vision("$N停下手，靠在身边的扫把上，抹了抹汗道："

                               "太累了太累了，歇歇再干。\n", me);



        me->delete_temp("work/" + NAME + "/step");

        return 1;

}



// 结束工作，领取奖励

public int finish_work(object me, object ob, object obj)

{

        mapping m;

        object coin;



        if (! objectp(obj) || environment(obj) != me)

                return fail_msg(ob->name() + "点点头道：“干完了？那就"

                                "快把工具还给店小二去呀。”\n");



        if (! (m = me->query_temp("work"))) 

                return 0;

        

        if (! mapp(m) || m[NAME]["state"] != 3)

        {

                write(CYN + ob->name() + "疑惑道：“你还没干完呢，就来"

                      "要奖励？”\n" NOR);

                return 0;

        }



        switch (m[NAME]["type"])

        {

        case "wash":

                if (obj->query("id") != "dish")

                {

                        write(CYN + ob->name() + "扫了一眼" + obj->name() +

                              "道：“这是我叫你洗的盘子？”\n" NOR);

                        return 0;

                }

                if (obj->query_amount() != m[NAME]["wash"])

                {

                        write(CYN + ob->name() + "数了数" + obj->name() +

                              "道：“这盘子的数目不对呀，给你打碎了？”\n" NOR);

                        return 0;

                }

                // 金钱报酬

                write(sort_msg(CYN + ob->name() + "看了看" + obj->name() +

                               "，点点头道：“嗯，还不错，这里是你的工钱，"

                               "收好了。”\n" NOR));

                coin = new("/clone/money/coin");

                coin->set_amount(BONUS * m[NAME]["wash"] * 2);

                coin->move(me, 1);

                break;



        case "sweep":

                if (obj->query("id") != "besom")

                {

                        write(CYN + ob->name() + "扫了一眼" + obj->name() +

                              "道：“这是我给你的扫把？”\n" NOR);

                        return 0;

                }

                if (! arrayp(m[NAME]["place"]) || ! sizeof(m[NAME]["place"]))

                {

                        write(CYN + ob->name() + "瞪大眼睛望着你道：“你哪"

                              "里也没扫呀？”\n" NOR);

                        return 0;

                }

                // 金钱报酬

                write(sort_msg(CYN + ob->name() + "收起" + obj->name() +

                               "，点点头道：“嗯，还不错，这里是你的工钱，"

                               "收好了。”\n" NOR));

                coin = new("/clone/money/coin");

                coin->set_amount(BONUS * sizeof(m[NAME]["place"]) * 2);

                coin->move(me, 1);

                break;



        default:

                write(CYN + ob->name() + "抓了抓脑袋道：“你干的这是什"

                      "么呢？我怎么不知道呀。”\n" NOR);

                return 0;

        }

        // 清除工作的信息

        me->delete_temp("work");

        return 1;

}



mixed *query_info() { return ({ NAME, BONUS, MAX_NUM, MIN_EXP, MAX_EXP }); }

