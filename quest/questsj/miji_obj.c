// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping miji_obj = ([
        "/d/yanziwu/obj/dodgebook":30,                //百曲湖
        "/d/gaibang/obj/staff_book":33,               //彭有敬
        "/d/changan/npc/obj/book_unarmed":7,          //书痴
        "/d/changan/npc/obj/book_blade":7,            //书痴
        "/clone/book/zixia_book":1,                   //暂时无处获取
        "/clone/book/zijin_book":33,                  //童百熊
        "/clone/book/zihui-book":33,                  //慕容搏
        "/clone/book/zhemei_book2":30,                //灵鹫密室
        "/clone/book/zhemei_book1":30,                //灵鹫密室
        "/clone/book/zhanyi":30,                      //血棋衣
        "/clone/book/zhangfapu":33,                   //孙不二
        "/clone/book/yunvjing2":30,                   //林朝英
        "/clone/book/yunvjing1":30,                   //小龙女
        "/clone/book/yunu_book":30,                   //华山居室
        "/clone/book/yljianpu":1,                     //暂时无处获取
        "/clone/book/yljian":1,                       //暂时无处获取
        "/clone/book/ylbian":1,                       //暂时无处获取
        "/clone/book/yijinjing":33,                   //任我行
        "/clone/book/xx-book":30,                     //梅庄牢房
        "/clone/book/xuanfeng_book":30,               //黄药师
        "/clone/book/wuji4":33,                       //少林藏经楼二楼
        "/clone/book/wuji3":30,                       //少林藏经楼二楼
        "/clone/book/wuji2":30,                       //少林藏经楼二楼
        "/clone/book/wuji1":30,                       //少林藏经楼二楼
        "/clone/book/throw_book":33,                  //摘星子
        "/clone/book/sword_book2":30,                 //华山书房
        "/clone/book/sword_book":33,                  //王小二
        "/clone/book/sun_book":1,                     //暂时无处获取
        "/clone/book/strike_book":33,                 //苟读
        "/clone/book/staff_book":33,                  //丐帮密室（白世镜所在地）
        "/clone/book/skin":28,                        //雪山藏经阁
        "/clone/book/six_book":33,                    //枯荣禅师
        "/clone/book/shoufa":36,                      //陆高轩
        "/clone/book/shenghuo-ling":33,               //张无忌
        "/clone/book/qunxing-tu":1,                   //暂时无处获取
        "/clone/book/quanpu":1,                       //暂时无处获取
        "/clone/book/qijianpu":30,                    //灵鹫密室
        "/clone/book/qiankun_book":30,                //明教密室
        "/clone/book/pixie_book":60,                  //华山山崖
        "/clone/book/parry_book":7,                   //书店老板购买
        "/clone/book/liuyang_book2":30,               //灵鹫密室
        "/clone/book/liuyang_book1":30,               //灵鹫密室
        "/clone/book/jiuyin2":30,                     //古墓后厅、黄药师
        "/clone/book/jiuyin1":30,                     //古墓后厅
        "/clone/book/jiuyang-book":33,                //昆仑谷底
        "/clone/book/jinyantu":33,                    //马钰
        "/clone/book/jinshe3":26,                     //华山山洞
        "/clone/book/jinshe2":26,                     //华山山洞
        "/clone/book/jinshe1":26,                     //华山山洞
        "/clone/book/hujia-book":33,                  //胡斐
        "/clone/book/hand_book":33,                   //康广陵
        "/clone/book/force_book":30,                  //宋远桥
        "/clone/book/dujing_2":30,                    //丁春秋
        "/clone/book/douzhuan-book":30,               //慕容博
        "/clone/book/bufa":36,                        //陆高轩
        "/clone/book/book-stone":20,                  //少林碑林、神龙岛小屋、侠客岛书房、雪山藏经阁、燕子钨还施水阁
        "/clone/book/book-silk":26,                   //少林大雄宝殿、侠客岛书房、雪山藏经阁、燕子钨还施水阁
        "/clone/book/book-iron":18,                   //打铁僧、神龙小屋、侠客岛书房、雪山藏经阁、燕子钨还施水阁
        "/clone/book/book-bamboo":18,                 //达摩洞、神龙小屋、侠客岛书房、雪山藏经阁、燕子钨还施水阁
        "/clone/book/bojuan":1,                       //暂时无处获取
        "/clone/book/blade-book":36,                  //胡斐
        "/clone/book/18niou":30,                      //大悲老人
        "/clone/book/18muou":30,                      //大悲老人
]);

int check_value(string filename)
{
        if (undefinedp(miji_obj[filename])) return 0;
        return miji_obj[filename];
}
