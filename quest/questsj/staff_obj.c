// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping staff_obj = ([
        "/d/xueshan/obj/senggun":18,                  //雪山六个僧兵、葛伦布
        "/d/xueshan/obj/mugun":22,                    //雪山库房
        "/d/xueshan/obj/fachu":25,                    //雪山祭祀喇嘛（四个）
        "/d/xiangyang/npc/obj/mugun":5,               //襄阳木匠购买
        "/d/village/npc/obj/stick":5,                 //峨嵋小贩、少林小贩、武功镇小贩
        "/d/tulong/yitian/npc/obj/tiezhang":20,       //杖僧
        "/d/tulong/yitian/npc/obj/spear":10,          //蒙古官兵（二十五个）
        "/d/tulong/tulong/npc/obj/flag":25,           //王盘山岛边四个教众
        "/d/shaolin/obj/qimeigun":16,                 //澄寂、澄灵、慧洁尊者、慧虚尊者、道尘禅师索要
        "/d/shaolin/obj/chanzhang":12,                //贡唐仓国师、澄灭、澄欲、慧空尊者、慧修尊者、玄难大师、道尘禅师索要
        "/d/quanzhou/npc/obj/huoqiang":35,            //红毛鬼
        "/d/quanzhen/npc/obj/stick":5,                //全真小贩
        "/d/mingjiao/obj/qimeigun":35,                //闻苍松
        "/d/mingjiao/obj/langyabang":30,              //吴劲草、庄铮
        "/d/mingjiao/obj/chanzhang":1,                //暂时无处获取
        "/d/huanghe/npc/obj/tieqiao":30,              //采石人（两个）
        "/d/huanghe/npc/obj/fork":35,                 //侯通海
        "/d/heimuya/npc/obj/shutonggun":32,           //张乘风、张乘云
        "/d/heimuya/npc/obj/leizhendang":35,          //赵鹤
        "/d/heimuya/npc/obj/gangzhang":35,            //上官云
        "/d/hangzhou/obj/shuzhi":15,                  //杭州山路、苏州虎丘山、黄河树林
        "/d/hangzhou/honghua/obj/tiejiang":30,        //蒋四根、沙通天
        "/d/guiyun/npc/obj/gancheng":35,              //全金发
        "/d/guiyun/npc/obj/biandan":8,                //南希仁、买卖提购买
        "/d/foshan/obj/shuzhi":18,                    //佛山林间道
        "/d/city/obj/zhubang":5,                      //扬州林间小屋、苏州小贩购买、侠客岛武器库
        "/d/city/obj/shuzhi":10,                      //好多地方都有
        "/d/city/obj/branch4":16,                     //蛇谷
        "/d/city/obj/branch3":16,                     //蛇谷
        "/d/city/obj/branch2":16,                     //蛇谷
        "/d/city/npc/obj/zhubang":1,                  //暂时无处获取
        "/d/changan/npc/obj/shawei":22,               //长安衙役（四个）
        "/d/changan/npc/obj/gangzhang":1,             //暂时无处获取
        "/d/baituo/obj/shezhang":25,                  //白驼武器库、欧阳峰
        "/d/baituo/obj/lingshezhang":10,              //向欧阳峰要，无限多个
        "/d/baituo/npc/obj/shezhang":1,               //暂时无处获取
        "/clone/weapon/zhubang":10,                   //燕子坞试剑台、屠龙居
        "/clone/weapon/xiangmo-chu":35,               //达而巴
        "/clone/weapon/tiegun":5,                     //到处都有
        "/clone/weapon/qimeigun":1,                   //暂时无处获取
        "/clone/weapon/gshezhang":1,                  //暂时无处获取
        "/clone/weapon/gshezhan":15,                  //向欧阳克要
        "/clone/weapon/gangzhang":15,                 //很多随机NPC都有
        "/clone/weapon/changqiang":12,                //比较多
        "/clone/misc/bone":5,                         //人骨头
        "/kungfu/class/gaibang/yuzhu_zhang":35,       //洪七公
        "/kungfu/class/gaibang/obj/yuzhu_zhang":1,    //暂时无处获取
        "/kungfu/class/dali/obj/diaogan":35,          //褚万里
]);

int check_value(string filename)
{
        if (undefinedp(staff_obj[filename])) return 0;
        return staff_obj[filename];
}
