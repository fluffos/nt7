/*********************************************************
   本文件只被 hj_room1.c 使用。

   本房间描述带有图片，建议效果（即奈何所使用设置）：
   zmud4.62 32bit 汉化版， 宋体，小四(12)或小五(10) 查看，
   可得最佳效果。

   本房间支持两个 JOB。

   其一，杀了各族的族长时，可随机得到该族的权杖，搜集所有
         族的权杖，再回来这里发呆 JOB1_NEED_IDLE 秒，即可
         得到大量奖励。

   其二，在此发呆 JOB2_NEED_IDLE 秒，即得到 幽灵武士 JOB。
         杀了它可以得到额外的奖励。若被其他人杀去，与普通
         各族的NPC效果一样。本人杀了幽灵族武士时，可得到
         技能提升与游戏得分。

   JOB1 的发呆生效时间必须比 JOB2 的短。具体看下边的设置。

   另外，在此房间停留，会随机损失 hp ，至死方休！ 

   int query_idle( object target ) 返回发呆值 :)

   naihe 23:43 03-10-20
**********************************************************/


#include    "npc_obj/hj_settings/room_amount_hj.h"


#define        JOB1_NEED_IDLE       20
#define        JOB2_NEED_IDLE       31
#define        JOB1_AWARD           800
#define        JOB2_AWARD           80
#define        JOB2_AWARD_SKILLS    2

void full_all( object me );

int me_ok( object me )
{
    if( !me || !environment(me) || environment(me) != this_object()
       || query_temp("huanjing", me) != "start" || query_temp("hj_hp", me)<1 )
        return 0;

    return 1;
}


void create()
{
    set("j1_time", JOB1_NEED_IDLE );
    set("j2_time", JOB2_NEED_IDLE );

    set("room_mark",mark);
    set("short",MAG"幻境"NOR+GRN"·迷失之宝物隐匿之林"NOR);

    set("long", "你刚走过来，却发现这里是一小方水潭，水潭之水清幽平静，潭边立着一个
小亭(ting)。你只见月色清风，粼光闪烁，端的是舒心畅怀，清雅无比。你似乎
已忘了密林中的凶杀嘶喊，刚才的紧迫就似已离你而去。
                                                           [1;33m●[37;0m       
                                                                    
                                            [1;32m.. .[37;0m      [1;34mI[37;0m       [1;32m..[37;0m    
                                            [1;32m..[37;0m      [1;34m,'.`.[37;0m           
                                              [1;34m.__,-'.:::.`-.__,[37;0m  [1;32m.[37;0m  
                                               [1;34m~-------------~[37;0m      ");

    // string to long, 要分开来 set, 5555555
    set("long", query("long") + "
                                                 [1;31m_|=|___|=|_[37;0m        
                                           [1;34m.__,-'.:::::::::.`-.__,[37;0m  
                               [37m[37;0m             [1;34m~-------------------~[37;0m   
                               [37m |[37;0m              [1;31m_|_|_|___|_|_|_[37;0m      
                               [37m###################################[37;0m  
[42m     [30m▂▃▄▅▆▇▆▅▄▅▆▅▄▃▂▁▂▃▄▅▆▇█▇▆▅▄▃▂▁   [37;0m
        \n");

    // 奈何注：此图复制自哈工大BBS，颜色设置与其并无二致。亭外岸边的一竖是我加上的，
    // 为了一些其他的效果。
    // 忘记原作是谁了，在 HJ 毫无商业用途之时，这个图将保留。
    // 本图亦是奈何的单机上的 welcome 图，HOHO。可惜我对画这个东西
    // 毫无感觉，看这画的是多美……建议效果：
    // zmud4.62 32bit 汉化版， 宋体，小四（12） 查看，可得最佳效果。
    // naihe 23:25 03-10-20

    set("item_desc",([
        "亭"   : "这是一个小亭子，精致风雅。亭外岸边立着一柄权杖(zhang)，十分粗大。\n",
        "小亭" : "这是一个小亭子，精致风雅。亭外岸边立着一柄权杖(zhang)，十分粗大。\n",
        "ting" : "这是一个小亭子，精致风雅。亭外岸边立着一柄权杖(zhang)，十分粗大。\n",
        "杖"   : "这是一柄权杖，似乎散发着一股诡异的气息。它上边刻有一些小字(zi)。\n",
        "权杖" : "这是一柄权杖，似乎散发着一股诡异的气息。它上边刻有一些小字(zi)。\n",
        "zhang": "这是一柄权杖，似乎散发着一股诡异的气息。它上边刻有一些小字(zi)。\n",
        "字"   : "「幽灵之族权杖 -- 幽灵的武士将由此降临，暗夜的密林即将展开激战」\n",
        "小字" : "「幽灵之族权杖 -- 幽灵的武士将由此降临，暗夜的密林即将展开激战」\n",
        "zi"   : "「幽灵之族权杖 -- 幽灵的武士将由此降临，暗夜的密林即将展开激战」\n",
        ]) );

    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("invalid_startroom",1);

    set("exits",([
        "east" : __DIR__"hj_room2", 
        "south" : __DIR__"hj_room11",
        "southeast" : __DIR__"hj_room12",
        ]) );

    setup();
}

void init()
{
    // 所有的共有动作(即 all_room_info_hj.h 及 1_room_info_special.h 共有)
#include "all_common_init.h"

    // 升级功能！！！
    add_action("do_lvup", ({ "levelup", "lvup" }) );
    // npc 进入此地，不管是什么人，立刻离开
    if( query("hj_game/npc", me) )
        call_out("npc_out", 1, me);
    // 启动检测 me 的程序
    if( query_temp("huanjing", me) == "start" )
        call_out("start_check",2,me,query("id", me));
}

// 所有的共有函数(即 all_room_info_hj.h 及 1_room_info_special.h 共有)
#include "all_common_func.h"

void npc_out( object me )
{
    object outroom;
    int or;

    if( !me ) return;
    if( !environment(me) || environment(me) != this_object() )
        return;

    message_vision("$N左右看了一下，急急忙忙地离开了。\n", me);
    if( random(2) ) or = 2;
    else if( random(2) ) or = 11;
    else or = 12;

    outroom = find_object( __DIR__"hj_room"+or );
    if( !outroom ) outroom = load_object( __DIR__"hj_room" + or );
    me->move( outroom );
    message_vision("$N急急忙忙地走了过来。\n", me);
}

void start_check( object me, string id )
{
    if( !me_ok(me) )
    {
        delete("checking_job1_"+ id );
        delete("checking_job2_"+ id );
        delete("checking_lost_hp_"+ id );
        return;
    }

    // 开始执行此人的发呆判断及扣血程序

    // 并未在执行 checking 此人的 job1 函数，可以进行
    if( !query("checking_job1_"+ id ) )
    {
        set("checking_job1_"+ id, 1);
        call_out( "checking_job1", 5 + random(6), me, id);
    }
    // 同上
    if( !query("checking_job2_"+ id ) )
    {
        if( !query_temp("hj_youling_job", me) )
        {
            set("checking_job2_"+id, 1);
            call_out( "checking_job2", 5 + random(6) , me, id );
        }
    }
    // 同上及上上
    if( !query("checking_lost_hp_"+id) )
    {
        set("checking_lost_hp_"+ id, 1);
        call_out( "lost_hp", 1, me, id );
    }
}

// 在这个地点停留，会不断地掉HP，直到死为止。
void lost_hp( object me, string id )
{
    if( !me || !me_ok(me) )
    {
        delete("checking_lost_hp_"+ id );
        return;
    }

    // 随机 lost hp.
    if( random(3) )
    {
        call_out("lost_hp", 5+random(6), me, id );
        return;
    }

    write(HIB"你忽地感到一阵强烈的诡异气息不知从哪儿散发出来，只觉得心烦气闷，竟似灵魂正在与自己远离一般！\n"NOR);
    addn_temp("hj_hp", -(5+random(16)), me);
    call_out("lost_hp", 5+random(6), me, id);
}

// 这是搜集各族权杖的 JOB。
void checking_job1( object me, string id )
{
    string *job1_ids;
    string msg;
    object *job1_obj_list, temp;
    int i, award_score;

    // 断线的玩家调用 query_idle() 会出 bug
    if( !me || !me_ok(me) || !interactive(me) )
    {
        delete("checking_job1_"+ id );
        return;
    }
    if( query_idle(me) < JOB1_NEED_IDLE )
    {
        call_out("checking_job1", 5+random(6), me, id);
        return;
    }

    // 发呆时间到
    job1_ids = ({ "manye quanzhang", "mengli quanzhang", "aiyao quanzhang",
            "shanguai quanzhang", "juren quanzhang", });

    job1_obj_list = ({ });

    // 查看其是否有全套权杖
    for( i=0;i<sizeof( job1_ids ); i++ )
    {
        temp = present( job1_ids[i] , me );

        // 发现任何一个不够，退出检测程序。
        if( !temp )
        {
            delete("checking_job1_" + id );
            return;
        }
        job1_obj_list += ({ temp });
    }
    // 好的！获得奖励。
    message_vision( HIY"$N"HIY"正在凝神细思，忽地自己所带权杖都发出了耀眼光芒，不约而同地指向幽灵族的权杖！\n"NOR,me);
    msg = HIY + "";
    // 权杖没有颜色的设置，所以顿号这里也不用写颜色了。
    for( i=0; i<sizeof( job1_obj_list ); i++ )
    {
        if( i == 0 )
            msg += job1_obj_list[i] -> name(1);
        else msg += sprintf( "、%s", job1_obj_list[i] -> name(1) );
        destruct( job1_obj_list[i] );
    }

    message_vision( msg +"……\n只见各个权杖接连飞出，犹如飞蛾扑火般撞向幽灵族权杖，竟全部消失不见了！\n$N"HIY"眼看此景，奇异莫名，只惊得说不出话来。\n"NOR, me );

    delete("checking_job1_"+ id );
    award_score = JOB1_AWARD + random( JOB1_AWARD / 10 );
    addn_temp("hj_score", award_score, me);
    tell_object( me, HIR"游戏提示：你的得分增加了 "+award_score+" 点！\n"NOR );
    return;
}

// 这是去杀幽灵族武士的JOB。
void checking_job2( object me, string id )
{
    object kill_npc, rooms, ling;
    int random_room, yeah = 0;

    // 如果 me 不符合条件，或者 me 已经有 JOB 在身了，结束检测函数。
    // 这个 JOB 标记是 object 型的，当NPC被别人杀了，JOB会自动结束 :)
    if( !me || !me_ok(me) || query_temp("hj_youling_job", me) || !interactive(me) )
    {
        delete("checking_job2_"+ id );
        return;
    }
    // 这是一个特别判断。当玩家成功从臣民处得到宝物的重要组合部分时，
    // 将可得到一个“幽灵之令”，有此令在身者，将可以加倍速度得到武士JOB。
    // 此令必须是属于该玩家的。如玩家身上携带过多的令而又发生令牌未执行
    // 自毁程序的情况，则会产生令牌无效的非BUG类错误。
    ling = present( "youling ling", me);
    if( ling && query("my_master", ling) == me
         && query("this_time_mark", ling) == query_temp("this_time_mark", me) )
    {
        yeah = 1;
        if( query_idle(me) < JOB2_NEED_IDLE/2 )
        {
            call_out("checking_job2", 5+random(6), me, id);
            return;
        }
    }
    if( !yeah && query_idle(me) < JOB2_NEED_IDLE )
    {
        call_out("checking_job2", 5+random(6), me, id);
        return;
    }

    if( yeah && ling )
        message_vision( HIB"$N"HIB"身上的$n"HIB"忽然发出一阵鬼魅之声，周围骤地厉声四起，似是响起了一片呼应！\n"NOR, me, ling);

    // 成功！发放JOB。
    delete("checking_job2_"+id);
    kill_npc = new( __DIR__"npc_obj/hj_npc_kill" );
    kill_npc->setme( 88 );  // 特殊的 set.

    set("job_master_obj", me, kill_npc);
    set("job_award_score", JOB2_AWARD*9/10+random(JOB2_AWARD/5), kill_npc);
    switch( random(10) )
    {
        // 这个是随机奖励 me 的某项技能提升多少级
        case 0..1 :set("job_award_skills", JOB2_AWARD_SKILLS + random(2), kill_npc );
            break;
        // 或者奖励一点力量，因为力量值很重要，所以不可多奖
        case 8 :set("job_award_power", 1, kill_npc );
            break;
    }
    // 设置一些描述，并且也可以以此为依据，判断是否自己的NPC，不要白打（很难打！）。
    set("gender",query("gender",  me), kill_npc);
    set("long",query("long",  kill_npc)+"这人看起来竟与"+query("name", me)+"一模一样！\n", kill_npc);
    set("per",query("per",  me), kill_npc);

    random_room = 2 + random( HJ_ROOM_AMOUNT -1 );
    rooms = find_object( __DIR__"hj_room" + random_room );
    if( !rooms ) rooms = load_object( __DIR__"hj_room" + random_room );
    kill_npc->move( rooms );
    message_vision( BLU"忽地一阵阴风掠起，$N"NOR+BLU"骤然现身，诡异之极。\n"NOR, kill_npc);
    // JOB 奖励由该 npc 实现。

    set_temp("hj_youling_job", kill_npc, me);
    // 给 me 设置标记，不会继续发放JOB。
    // 以 object 型来设置JOB，当该NPC死掉(destruct)时，JOB自然结束。

    message_vision( BLU"\n$N"NOR+BLU"正在凝神细思，忽然间只听得幽灵之族权杖发出一阵枭叫之声！\n"
        "一个模糊的影子从权杖中激射而出，竟然穿过$N"NOR+BLU"的身体，往外边急冲而去！\n"
        "$N"NOR+BLU"惊魂未定，似已呆住，恍惚中见得影子似乎是往 "HIR"\""+random_room+"\""NOR+BLU" 去了。\n\n"NOR, me);
    me->start_busy(3);
    // ok,finish.
}

// 非常难的升级制度
// naihe 05-9-3 18:18 按：好象又不是很难。我5天冲到 lv6, lv6 是什么概念？……很强悍了
// 提高升级难度。
int do_lvup(string arg)
{
    object me = this_player(), rooms;
    int next_lv, score_need, power_need, f_sks_need, y_sks_need, l_sks_need, d_sks_need, heal_sks_need, dh_sks_need, fh_sks_need, gs_sks_need;
    string msg;

    int t;

    if( !me_ok(me) ) return 0;

    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return notify_fail("你还忙着呢，那么重要的事情还是等有空的时候再说吧。\n");

    next_lv=query("huanjing2003/lv", me)+1;
    if( next_lv > 9 ) return notify_fail("你现在已经是最高的等级了！\n");

    rooms = find_object( __DIR__"room_door_hj" );
    if( !rooms ) rooms = load_object( __DIR__"room_door_hj" );
    if( !rooms ) return notify_fail("现在谁都不能升级。\n");

    switch( next_lv )
    {
// ######################################################
// 此时，无任何自动保持，所以容易升

        case 1: msg = "1001点得分"; score_need = 1001;
            break;


// ######################################################
// 此时，sks 已可自动保持 5 lv
// 早期的 power 很容易升上去，所以 power 起点定为21点。

        case 2: msg = "1001点得分，风、雨、雷、电技能各31级，21点力量";
                score_need = 1001; t = 31; power_need = 21;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
            break;


// ######################################################
// 此时，sks 已可自动保持 10 lv

        case 3: msg = "1001点得分，风、雨、雷、电技能各41级，26点力量";
                score_need = 1001; t = 41; power_need = 26;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
            break;


// ######################################################
// 此时，sks 已可自动保持 15 lv
// 这是一个关键点，升了本级后，sks lv 可保持 20，即可以
// 使用 yun 特殊技。所以，要求高些

        case 4: msg = "999 点得分，风、雨、雷、电、恢复、夺魂、飞火、"
                        "滚石技能各41级，31点力量";
                score_need = 999; t = 41; power_need = 31;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// 此时，sks 已可自动保持 20 lv

        case 5: msg = "1001点得分，风、雨、雷、电、恢复、夺魂、飞火、"
                        "滚石技能各51级，31点力量";
                score_need = 1001; t = 51; power_need = 31;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// 此时，sks 已可自动保持 25 lv
// 这个升级条件和 lv 5 一样，但是相对容易些了

        case 6: msg = "1001点得分，风、雨、雷、电、恢复、夺魂、飞火、"
                        "滚石技能各51级，31点力量";
                score_need = 1001; t = 51; power_need = 31;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// 此时，sks 已可自动保持 30 lv

        case 7: msg = "1001点得分，风、雨、雷、电、恢复、夺魂、飞火、"
                        "滚石技能各61级，36点力量";
                score_need = 1001; t = 61; power_need = 36;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// 此时，sks 已可自动保持 35 lv
// 这又是一个关键点，up lv 后，将可保持 sks 40, 即可以 pfm.
// 特别难！
        case 8:msg = "88点得分，风、雨、雷、电、恢复、夺魂、飞火、"
                        "滚石技能各88级，41点力量";
                score_need = 88; t = 88; power_need = 41;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// 此时，sks 已可自动保持 40 lv
// 这是最后的一级，如果有人配合，那倒不算挺难 :)
// 因为力量的要求降低了
// sks 的要求很容易达到的，hoho

        case 9:msg = "1888点得分，风、雨、雷、电、恢复、夺魂、飞火、"
                        "滚石技能各66级，31点力量，\n"
                "并且在升级后，你所有的技能、力量都将被清除！";
                score_need = 1888; t = 66; power_need = 31;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;
    }

// ######################################################
// ######################################################
// ######################################################


    write( "你将升到第 "+next_lv+" 级，需要 "+msg+" 。\n");
    if( !arg || arg != "now")
        return notify_fail("如确实想升级，请输入 <levelup now> 。升级后，将会对应所需条件对你的各项能力进行削减。\n");

// 开始升级

    if( score_need && query_temp("hj_score", me)<score_need )
        return notify_fail("你没有足够的得分。\n");

    if( power_need && query_temp("hj_game_mepower", me)<power_need )
        return notify_fail("你没有足够的力量。\n");

    if( f_sks_need && (!query_temp("hj_game_skills/hfzj", me )
               || query_temp("hj_game_damages/hfzj", me)<f_sks_need) )
        return notify_fail("你的「呼风之技」等级不够。\n");

    if( y_sks_need && (!query_temp("hj_game_skills/hyzj", me )
               || query_temp("hj_game_damages/hyzj", me)<y_sks_need) )
        return notify_fail("你的「唤雨之技」等级不够。\n");

    if( l_sks_need && (!query_temp("hj_game_skills/llzj", me )
               || query_temp("hj_game_damages/llzj", me)<l_sks_need) )
        return notify_fail("你的「落雷之技」等级不够。\n");

    if( d_sks_need && (!query_temp("hj_game_skills/ydzj", me )
               || query_temp("hj_game_damages/ydzj", me)<d_sks_need) )
        return notify_fail("你的「引电之技」等级不够。\n");

    if( heal_sks_need && (!query_temp("hj_game_skills/heal", me )
               || query_temp("hj_game_damages/heal", me)<heal_sks_need) )
        return notify_fail("你的「恢复之技」等级不够。\n");

    if( dh_sks_need && (!query_temp("hj_game_skills/dhzj", me )
               || query_temp("hj_game_damages/dhzj", me)<dh_sks_need) )
        return notify_fail("你的「夺魂之技」等级不够。\n");

    if( fh_sks_need && (!query_temp("hj_game_skills/fhzj", me )
               || query_temp("hj_game_damages/fhzj", me)<fh_sks_need) )
        return notify_fail("你的「飞火之技」等级不够。\n");

    if( gs_sks_need && (!query_temp("hj_game_skills/gszj", me )
               || query_temp("hj_game_damages/gszj", me)<gs_sks_need) )
        return notify_fail("你的「滚石之技」等级不够。\n");

// all ok now!

    set("huanjing2003/lv", next_lv, me);
    if( score_need)addn_temp("hj_score", -(score_need-1), me);
    if( power_need)addn_temp("hj_game_mepower", -(power_need-1), me);
    if( f_sks_need)addn_temp("hj_game_damages/hfzj", -(f_sks_need-1), me);
    if( y_sks_need)addn_temp("hj_game_damages/hyzj", -(y_sks_need-1), me);
    if( l_sks_need)addn_temp("hj_game_damages/llzj", -(l_sks_need-1), me);
    if( d_sks_need)addn_temp("hj_game_damages/ydzj", -(d_sks_need-1), me);
    if( heal_sks_need)addn_temp("hj_game_damages/heal", -(heal_sks_need-1), me);
    if( dh_sks_need)addn_temp("hj_game_damages/dhzj", -(dh_sks_need-1), me);
    if( fh_sks_need)addn_temp("hj_game_damages/fhzj", -(fh_sks_need-1), me);
    if( gs_sks_need)addn_temp("hj_game_damages/gszj", -(gs_sks_need-1), me);

    if( query_temp("hj_game_mepower", me)<5 )
        set_temp("hj_game_mepower", 5, me);
    set("huanjing2003/last_power",query_temp("hj_game_mepower",  me), me);
    set("huanjing2003/last_skills_lv",query_temp("hj_game_damages",  me), me);

// 9级将清除所有累积，但累积次数还有效
    if( next_lv == 9 )
    {
        delete("huanjing2003/last_power", me);
        delete("huanjing2003/last_skills_name", me);
        delete("huanjing2003/last_skills_lv", me);
        delete("huanjing2003/last_hp_max", me);
        delete_temp("hj_game_skills", me);
        delete_temp("hj_game_damages", me);
        set_temp("hj_game_mepower", 10, me);
        set_temp("hj_hp_max", 700, me);
        set_temp("hj_game_skills/heal", "恢复之技", me);
        set_temp("hj_game_damages/heal", 3+random(8), me);
    }

    me->save();
    me->start_busy(5);

    message_vision( HIW"\n\n$N"HIW"大喝一声，念咒文道：“浮云清风，尽纳我怀，幽灵再现，予我力量！”\n\n"
        "只见$N"HIW"全身银光闪耀，能力修为明显地上了一个层次！\n\n\n"NOR, me);

    rooms->save_player_level(query("name", me),query("id", me),query("huanjing2003/lv", me),time());
    return 1;
}
