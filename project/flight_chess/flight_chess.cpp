#include "Chess.h"
#include "Ground.h"
#include "Player.h"

#include <iostream>
#include <graphics.h>
#include <easyx.h>

using namespace std;



void button(int x, int y, int w, int h, const TCHAR * text)
{
    setbkmode(TRANSPARENT);
    setlinecolor(LIGHTBLUE);
    rectangle(x, y, x+w, y+h);

    settextstyle(30, 0, _T("微软雅黑"));
    settextcolor(BLACK);
    int tx = x + (w - textwidth(text)) / 2;
    int ty = y + (h - textheight(text)) / 2;
    outtextxy(tx, ty, text);
}


int set_computer_num(int n)
{
    if (n == 2)
    {
        cout << "玩家总数为2，其中1个电脑玩家\n";
        return 1;
    }
        

    settextstyle(50, 0, L"华文行楷");
    outtextxy(325, 200, L"请选择其中电脑玩家的数量");

    ExMessage msg;
    if (n == 3)
    {
        button(350, 400, 200, 60, L"1");
        button(650, 400, 200, 60, L"2");
        while (1)
        {
            if (peekmessage(&msg, EM_MOUSE))
            {
                switch (msg.message)
                {
                case WM_LBUTTONDOWN:
                    if (msg.x >= 350 && msg.x <= 550 && msg.y >= 400 && msg.y <= 460)
                    {
                        cout << "玩家总数为3，其中1个电脑玩家\n";
                        return 1;
                    }
                    if (msg.x >= 650 && msg.x <= 850 && msg.y >= 400 && msg.y <= 460)
                    {
                        cout << "玩家总数为3，其中2个电脑玩家\n";
                        return 2;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
    if (n == 4)
    {
        button(200, 450, 200, 100, L"1");
        button(500, 450, 200, 100, L"2");
        button(800, 450, 200, 100, L"3");
        while (1)
        {
            if (peekmessage(&msg, EM_MOUSE))
            {
                switch (msg.message)
                {
                case WM_LBUTTONDOWN:
                    if (msg.x >= 200 && msg.x <= 400)
                    {
                        cout << "玩家总数为4，其中1个电脑玩家\n";
                        return 1;
                    }

                    if (msg.x >= 500 && msg.x <= 700)
                    {
                        cout << "玩家总数为4，其中2个电脑玩家\n";
                        return 2;
                    }

                    if (msg.x >= 800 && msg.x <= 1000)
                    {
                        cout << "玩家总数为4，其中3个电脑玩家\n";
                        return 3;
                    }
                    break;
                default:
                    break;
                }
            }
        }

    }
}


int roll_dice(int n, Player player[])
{
    int a;
    a = rand() % 6 + 1;
    if (player[n].is_computer)
        cout << "PLAYER " << n + 1 << "（电脑） 掷出 " << a << " 点\n";
    else
        cout << "PLAYER " << n + 1 << " 掷出 " << a << " 点\n";
    return a;
}


void show_dice(int n)
{
    TCHAR s = n + '0';
    setfillcolor(WHITE);
    settextstyle(50, 0, _T("微软雅黑"));
    settextcolor(BLACK);
    outtextxy(960, 55, s);
}


void show_move(Player player[])
{
    IMAGE qp;
    loadimage(&qp, _T("./QiPan.png"));
    putimage(0, 0, &qp);

    setlinestyle(PS_SOLID, 2);
    setlinecolor(BLACK);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == 0)
                setfillcolor(YELLOW);
            if (i == 1)
                setfillcolor(LIGHTBLUE);
            if (i == 2)
                setfillcolor(LIGHTRED);
            if (i == 3)
                setfillcolor(LIGHTGREEN);

            fillcircle(player[i].chess[j].chess_ground->x, player[i].chess[j].chess_ground->y, 10);
        }
    }
}


void set_fill_color(Player player)
{
    if (player.player_color == PYellow)
        setfillcolor(YELLOW);
    else if (player.player_color == PBlue)
        setfillcolor(LIGHTBLUE);
    else if (player.player_color == PRed)
        setfillcolor(LIGHTRED);
    else if (player.player_color == PGreen)
        setfillcolor(LIGHTGREEN);
}


void show_winner(int winner)
{
    IMAGE background;
    loadimage(&background, _T("./bg.png"));
    putimage(0, 0, &background);
    settextcolor(LIGHTBLUE);
    settextstyle(70, 0, L"华文行楷");
    if (winner == 1)
        outtextxy(170, 300, L"恭喜 PLAYER 1 获得最终胜利！");
    if (winner == 2)
        outtextxy(170, 300, L"恭喜 PLAYER 2 获得最终胜利！");
    if (winner == 3)
        outtextxy(170, 300, L"恭喜 PLAYER 3 获得最终胜利！");
    if (winner == 4)
        outtextxy(170, 300, L"恭喜 PLAYER 4 获得最终胜利！");
}




int main()
{
    int total_num, player_num;
    int debug = 0;


    // 设置初始界面
    initgraph(1200, 700, SHOWCONSOLE);
    setbkcolor(WHITE);
    cleardevice();
    IMAGE background;
    loadimage(&background, _T("./bg.png"));
    putimage(0, 0, &background);

    settextstyle(150, 0, _T("华文行楷"));
    settextcolor(BLACK);
    outtextxy(350, 200, L"飞 行 棋");

    button(450, 400, 300, 75, L"开始游戏");
    button(450, 500, 300, 75, L"以DEBUG模式游戏");
    ExMessage msg;
    while (1)
    {
        int f = 0;
        if (peekmessage(&msg, EM_MOUSE))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 450 && msg.x <= 750 && msg.y >= 400 && msg.y <= 475)
                {
                    f = 1;
                }
                if (msg.x >= 450 && msg.x <= 750 && msg.y >= 500 && msg.y <= 575)
                {
                    f = 1;
                    debug = 1;
                }
                break;
            default:
                break;
            }
        }
        if (f == 1)
            break;
    }
    putimage(0, 0, &background);



    // 设置选择人数的界面
    settextstyle(50, 0, _T("华文行楷"));
    settextcolor(BLACK);
    outtextxy(440, 200, L"请选择玩家总数");

    button(200, 450, 200, 100, L"2");
    button(500, 450, 200, 100, L"3");
    button(800, 450, 200, 100, L"4");

    while (1)
    {
        int f = 0;
        if (peekmessage(&msg, EM_MOUSE))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.y >= 450 && msg.y <= 550)
                {
                    if (msg.x >= 200 && msg.x <= 400)
                    {
                        f = 1;
                        total_num = 2;
                        putimage(0, 0, &background);
                        player_num = 2 - set_computer_num(2);
                    }

                    if (msg.x >= 500 && msg.x <= 700)
                    {
                        f = 1;
                        total_num = 3;
                        putimage(0, 0, &background);
                        player_num = 3 - set_computer_num(3);
                        
                    }

                    if (msg.x >= 800 && msg.x <= 1000)
                    {
                        f = 1;
                        total_num = 4;
                        putimage(0, 0, &background);
                        player_num = 4 - set_computer_num(4);
                        
                    }
                }
                break;
            default:
                break;
            }
        }
        if (f == 1)
            break;
    }
    putimage(0, 0, &background);



    // 设置进入游戏等待界面
    settextstyle(150, 0, _T("华文行楷"));
    settextcolor(BLACK);
    outtextxy(300, 200, L"游戏开始！");

    Sleep(3000);
    putimage(0, 0, &background);
    cout << "游戏开始!!！\n";




    // 设置位置坐标
    Ground road_end[24] = {
        Ground(115, 350, 200, &road_end[1], &road_end[1], GWhite),
        Ground(154, 350, 201, &road_end[2], &road_end[0], GWhite),
        Ground(193, 350, 202, &road_end[3], &road_end[1], GWhite),
        Ground(232, 350, 203, &road_end[4], &road_end[2], GWhite),
        Ground(271, 350, 204, &road_end[5], &road_end[3], GWhite),
        Ground(316, 350, 205, &road_end[4], &road_end[4], GWhite),

        Ground(350, 115, 206, &road_end[7], &road_end[7], GWhite),
        Ground(350, 154, 207, &road_end[8], &road_end[6], GWhite),
        Ground(350, 193, 208, &road_end[9], &road_end[7], GWhite),
        Ground(350, 232, 209, &road_end[10], &road_end[8], GWhite),
        Ground(350, 271, 210, &road_end[11], &road_end[9], GWhite),
        Ground(350, 316, 211, &road_end[10], &road_end[10], GWhite),
        
        Ground(585, 350, 212, &road_end[13], &road_end[13], GWhite),
        Ground(546, 350, 213, &road_end[14], &road_end[12], GWhite),
        Ground(507, 350, 214, &road_end[15], &road_end[13], GWhite),
        Ground(468, 350, 215, &road_end[16], &road_end[14], GWhite),
        Ground(429, 350, 216, &road_end[17], &road_end[15], GWhite),
        Ground(385, 350, 217, &road_end[16], &road_end[16], GWhite),

        Ground(350, 585, 218, &road_end[19], &road_end[19], GWhite),
        Ground(350, 546, 219, &road_end[20], &road_end[18], GWhite),
        Ground(350, 507, 220, &road_end[21], &road_end[19], GWhite),
        Ground(350, 468, 221, &road_end[22], &road_end[20], GWhite),
        Ground(350, 429, 222, &road_end[23], &road_end[21], GWhite),
        Ground(350, 385, 223, &road_end[22], &road_end[22], GWhite)
    };

    Ground road[52] = {
        Ground(60, 350, 0, &road[1], &road_end[0], GYellow),
        Ground(60, 310, 1, &road[2], &road[5], GBlue),
        Ground(60, 273, 2, &road[3], &road[6], GRed),
        Ground(74, 232, 3, &road[4], &road[7], GGreen),
        Ground(115, 213, 4, &road[5], &road[8], GYellow),
        Ground(153, 213, 5, &road[6], &road[9], GBlue),
        Ground(193, 232, 6, &road[7], &road[10], GRed),
        Ground(230, 195, 7, &road[8], &road[19], GGreen),
        Ground(213, 154, 8, &road[9], &road[12], GYellow),
        Ground(213, 115, 9, &road[10], &road[13], GBlue),
        Ground(230, 73, 10, &road[11], &road[14], GRed),
        Ground(272, 59, 11, &road[12], &road[15], GGreen),
        Ground(312, 59, 12, &road[13], &road[16], GYellow),
        Ground(350, 59, 13, &road[14], &road_end[6], GBlue),
        Ground(390, 59, 14, &road[15], &road[18], GRed),
        Ground(429, 59, 15, &road[16], &road[19], GGreen),
        Ground(471, 74, 16, &road[17], &road[20], GYellow),
        Ground(489, 115, 17, &road[18], &road[21], GBlue),
        Ground(489, 154, 18, &road[19], &road[22], GRed),
        Ground(471, 195, 19, &road[20], &road[23], GGreen),
        Ground(506, 232, 20, &road[21], &road[32], GYellow),
        Ground(547, 213, 21, &road[22], &road[25], GBlue),
        Ground(585, 213, 22, &road[23], &road[26], GRed),
        Ground(627, 232, 23, &road[24], &road[27], GGreen),
        Ground(642, 273, 24, &road[25], &road[28], GYellow),
        Ground(642, 310, 25, &road[26], &road[29], GBlue),
        Ground(642, 350, 26, &road[27], &road_end[12], GRed),
        Ground(642, 388, 27, &road[28], &road[31], GGreen),
        Ground(642, 426, 28, &road[29], &road[32], GYellow),
        Ground(627, 468, 29, &road[30], &road[33], GBlue),
        Ground(585, 485, 30, &road[31], &road[34], GRed),
        Ground(547, 485, 31, &road[32], &road[35], GGreen),
        Ground(506, 468, 32, &road[33], &road[36], GYellow),
        Ground(471, 502, 33, &road[34], &road[45], GBlue),
        Ground(489, 545, 34, &road[35], &road[38], GRed),
        Ground(489, 583, 35, &road[36], &road[39], GGreen),
        Ground(471, 625, 36, &road[37], &road[40], GYellow),
        Ground(429, 640, 37, &road[38], &road[41], GBlue),
        Ground(390, 640, 38, &road[39], &road[42], GRed),
        Ground(350, 640, 39, &road[40], &road_end[18], GGreen),
        Ground(312, 640, 40, &road[41], &road[44], GYellow),
        Ground(272, 640, 41, &road[42], &road[45], GBlue),
        Ground(230, 625, 42, &road[43], &road[46], GRed),
        Ground(213, 583, 43, &road[44], &road[47], GGreen),
        Ground(213, 545, 44, &road[45], &road[48], GYellow),
        Ground(230, 502, 45, &road[46], &road[49], GBlue),
        Ground(193, 468, 46, &road[47], &road[6], GRed),
        Ground(153, 485, 47, &road[48], &road[51], GGreen),
        Ground(115, 485, 48, &road[49], &road[0], GYellow),
        Ground(74, 468, 49, &road[50], &road[1], GBlue),
        Ground(60, 426, 50, &road[51], &road[2], GRed),
        Ground(60, 388, 51, &road[0], &road[3], GGreen),
    };

    Ground yellow_start = Ground(20, 200, 101, &road[4], &road[4], GWhite);
    Ground red_start = Ground(680, 500, 103, &road[30], &road[30], GWhite);
    Ground green_start = Ground(200, 680, 104, &road[43], &road[43], GWhite);
    Ground blue_start = Ground(500, 20, 102, &road[17], &road[17], GWhite);

    Ground airport[16] = {
        // Yellow
        Ground(60, 60, -11, &yellow_start, &yellow_start, GWhite),
        Ground(60, 121, -12, &yellow_start, &yellow_start, GWhite),
        Ground(121, 60, -13, &yellow_start, &yellow_start, GWhite),
        Ground(121, 121, -14, &yellow_start, &yellow_start, GWhite),
        // Blue
        Ground(580, 60, -21, &blue_start, &blue_start, GWhite),
        Ground(580, 121, -22, &blue_start, &blue_start, GWhite),
        Ground(640, 60, -23, &blue_start, &blue_start, GWhite),
        Ground(640, 121, -24, &blue_start, &blue_start, GWhite),
        // Red
        Ground(580, 580, -31, &red_start, &red_start, GWhite),
        Ground(580, 641, -32, &red_start, &red_start, GWhite),
        Ground(641, 580, -33, &red_start, &red_start, GWhite),
        Ground(641, 641, -34, &red_start, &red_start, GWhite),
        // Green
        Ground(60, 580, -41, &green_start, &green_start, GWhite),
        Ground(60, 641, -42, &green_start, &green_start, GWhite),
        Ground(121, 580, -43, &green_start, &green_start, GWhite),
        Ground(121, 641, -44, &green_start, &green_start, GWhite)
    };

    
    // 设置游戏界面
    IMAGE QiPan;
    loadimage(&QiPan, _T("./QiPan.png"));
    putimage(0, 0, &QiPan);

    button(800, 50, 100, 65, L"掷骰子");
    fillrectangle(950, 60, 990, 100);
    settextstyle(40, 0, _T("华文行楷"));
    settextcolor(BLACK);
    outtextxy(1000, 65, L"点数");
    settextstyle(30, 0, _T("华文行楷"));
    outtextxy(800, 150, L"↑点击这里投掷骰子");

    button(800, 450, 100, 60, L"飞机1");
    button(800, 550, 100, 60, L"飞机2");
    button(1000, 450, 100, 60, L"飞机3");
    button(1000, 550, 100, 60, L"飞机4");
    settextstyle(30, 0, _T("华文行楷"));
    outtextxy(750, 380, L"↓点击下列按钮选择行动的飞机");
    


    // 玩家初始化
    Player player[4] = {
        Player(PYellow, 0),
        Player(PBlue, 0),
        Player(PRed, 0),
        Player(PGreen, 0)
    };

    for (int i = 0; i < total_num; i++)
    {
        if (i < player_num)
            player[i].is_computer = 0;
        else
            player[i].is_computer = 1;
    }
    

    // 初始化棋子
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (player[i].player_color == PYellow)
                player[i].chess[j] = Chess(CYellow, -10*(i+1) - j-1, &airport[j]);
            if (player[i].player_color == PBlue)
                player[i].chess[j] = Chess(CBlue, -10*(i+1) - j-1, &airport[4+j]);
            if (player[i].player_color == PRed)
                player[i].chess[j] = Chess(CRed, -10*(i+1) - j-1, &airport[8+j]);
            if (player[i].player_color == PGreen)
                player[i].chess[j] = Chess(CGreen, -10*(i+1) - j-1, &airport[12+j]);
        }
    }



    // 游戏主要逻辑
    int order = 1;
    int winner = -1;
    while (1) // 主循环,每循环一次为一个回合
    {
        for (int i = 0; i < player_num; i++) // 每回合真人玩家循环
        {
            while (1) // 获取鼠标事件，摇骰子循环
            {
                int f = 0;
                if (peekmessage(&msg, EM_MOUSE))
                {
                    switch (msg.message)
                    {
                    case WM_LBUTTONDOWN:
                        if (msg.x >= 800 && msg.x <= 900 && msg.y >= 50 && msg.y <= 110)
                        {
                            f = 1;
                            int a;
                            if (debug == 1)
                            {
                                cout << "请输入这次摇到的点数： ";
                                cin >> a;
                            }
                            else
                                a = roll_dice(i, player);
                            set_fill_color(player[i]);
                            fillrectangle(950, 60, 990, 100);
                            show_dice(a);

                            if (a == 6)
                            {
                                int all_off = 1;

                                for (int j = 0; j < 4; j++)
                                    if (player[i].chess[j].is_off == 0)
                                        all_off = 0;
                                // 骰子为 6 且有飞机未起飞
                                if (all_off == 0) 
                                {
                                    cout << "PLAYER " << i + 1 << " 请选择一架飞机进入跑道\n";
                                    // 获取鼠标事件，选飞机循环
                                    while (1) 
                                    {
                                        int f1 = 0;
                                        if (peekmessage(&msg, EM_MOUSE))
                                        {
                                            switch (msg.message)
                                            {
                                            case WM_LBUTTONDOWN:
                                                if (msg.x >= 800 && msg.x <= 900 && msg.y >= 450 && msg.y <= 510)
                                                {
                                                    if (player[i].chess[0].is_off == 0)
                                                    {
                                                        f1 = 1;
                                                        player[i].chess[0].set_off();
                                                        show_move(player);
                                                        cout << "PLAYER " << i + 1 << " 选择将" << 1 << "号飞机进入跑道\n";
                                                    }
                                                    else
                                                    {
                                                        cout << "该飞机已起飞。请重新选择\n";
                                                    }
                                                    
                                                }
                                                if (msg.x >= 800 && msg.x <= 900 && msg.y >= 550 && msg.y <= 610)
                                                {
                                                    if (player[i].chess[1].is_off == 0)
                                                    {
                                                        f1 = 1;
                                                        player[i].chess[1].set_off();
                                                        show_move(player);
                                                        cout << "PLAYER " << i + 1 << " 选择将" << 2 << "号飞机进入跑道\n";
                                                    }
                                                    else
                                                    {
                                                        cout << "该飞机已起飞。请重新选择\n";
                                                    }
                                                }
                                                if (msg.x >= 1000 && msg.x <= 1100 && msg.y >= 450 && msg.y <= 510)
                                                {
                                                    if (player[i].chess[2].is_off == 0)
                                                    {
                                                        f1 = 1;
                                                        player[i].chess[2].set_off();
                                                        show_move(player);
                                                        cout << "PLAYER " << i + 1 << " 选择将" << 3 << "号飞机进入跑道\n";
                                                    }
                                                    else
                                                    {
                                                        cout << "该飞机已起飞。请重新选择\n";
                                                    }
                                                }
                                                if (msg.x >= 1000 && msg.x <= 1100 && msg.y >= 550 && msg.y <= 610)
                                                {
                                                    if (player[i].chess[3].is_off == 0)
                                                    {
                                                        f1 = 1;
                                                        player[i].chess[3].set_off();
                                                        show_move(player);
                                                        cout << "PLAYER " << i + 1 << " 选择将" << 4 << "号飞机进入跑道\n";
                                                    }
                                                    else
                                                    {
                                                        cout << "该飞机已起飞。请重新选择\n";
                                                    }
                                                }
                                                break;
                                            default:
                                                break;
                                            }

                                            if (f1 == 1)
                                                break;
                                        }
                                    }
                                    cout << "PLAYER " << i + 1 << " 可以再掷一次骰子\n";
                                    f = 0;
                                }
                                // 骰子为 6 且飞机全飞出机场
                                else  
                                {
                                    cout << "PLAYER " << i + 1 << " 请选择前进的飞机\n";
                                    // 获取鼠标事件，选飞机循环
                                    while (1) 
                                    {
                                        int f1 = 0;
                                        if (peekmessage(&msg, EM_MOUSE))
                                        {
                                            switch (msg.message)
                                            {
                                            case WM_LBUTTONDOWN:
                                                if (msg.x >= 800 && msg.x <= 900 && msg.y >= 450 && msg.y <= 510)
                                                {
                                                    if (player[i].chess[0].has_finished == 0)
                                                    {
                                                        f1 = 1;
                                                        player[i].chess[0].move(6);

                                                        Ground * cg = player[i].chess[0].chess_ground;
                                                        if (cg->position == 205 || cg->position == 211 || cg->position == 217 || cg->position == 223)
                                                        {
                                                            player[i].chess[0].has_finished = 1;
                                                            player[i].goal_achieved++;
                                                            cout << "PLAYER " << i + 1 << " 的飞机到达终点，玩家目前得分为" << player[i].goal_achieved << "分\n";
                                                        }

                                                        for (int i1 = 0; i1 < 4; i1++)
                                                        {
                                                            if (i1 == i)
                                                                continue;
                                                            else
                                                                for (int j1 = 0; j1 < 4; j1++)
                                                                {
                                                                    if (player[i1].chess[j1].chess_ground == player[i].chess[0].chess_ground)
                                                                    {
                                                                        player[i1].chess[j1].chess_ground = &airport[i1*4 + j1];
                                                                        player[i1].chess[j1].is_off = 0;
                                                                        cout << "PLAYER " << i1 + 1 << " 的" << j1 + 1 << "号飞机被 PLAYER " << i + 1 << " 的飞机追上，返回机场\n";
                                                                    }
                                                                }
                                                        }

                                                        show_move(player);
                                                        cout << "PLAYER " << i + 1 << " 选择将" << 1 << "号飞机前进6格\n";
                                                    }
                                                    else
                                                    {
                                                        cout << "该飞机已到达终点，请重新选择\n";
                                                    }

                                                }
                                                if (msg.x >= 800 && msg.x <= 900 && msg.y >= 550 && msg.y <= 610)
                                                {
                                                    if (player[i].chess[1].has_finished == 0)
                                                    {
                                                        f1 = 1;
                                                        player[i].chess[1].move(6);
                                                        Ground* cg = player[i].chess[1].chess_ground;
                                                        if (cg->position == 205 || cg->position == 211 || cg->position == 217 || cg->position == 223)
                                                        {
                                                            player[i].chess[1].has_finished = 1;
                                                            player[i].goal_achieved++;
                                                            cout << "PLAYER " << i + 1 << " 的飞机到达终点，玩家目前得分为" << player[i].goal_achieved << "分\n";
                                                        }
                                                        for (int i1 = 0; i1 < 4; i1++)
                                                        {
                                                            if (i1 == i)
                                                                continue;
                                                            else
                                                                for (int j1 = 0; j1 < 4; j1++)
                                                                {
                                                                    if (player[i1].chess[j1].chess_ground == player[i].chess[1].chess_ground)
                                                                    {
                                                                        player[i1].chess[j1].chess_ground = &airport[i1*4 + j1];
                                                                        player[i1].chess[j1].is_off = 0;
                                                                        cout << "PLAYER " << i1 + 1 << " 的" << j1 + 1 << "号飞机被 PLAYER " << i + 1 << " 的飞机追上，返回机场\n";
                                                                    }
                                                                }
                                                        }
                                                        show_move(player);
                                                        cout << "PLAYER " << i + 1 << " 选择将" << 2 << "号飞机前进6格\n";
                                                    }
                                                    else
                                                    {
                                                        cout << "该飞机已到达终点，请重新选择\n";
                                                    }

                                                }
                                                if (msg.x >= 1000 && msg.x <= 1100 && msg.y >= 450 && msg.y <= 510)
                                                {
                                                    if (player[i].chess[2].has_finished == 0)
                                                    {
                                                        f1 = 1;
                                                        player[i].chess[2].move(6);
                                                        Ground* cg = player[i].chess[2].chess_ground;
                                                        if (cg->position == 205 || cg->position == 211 || cg->position == 217 || cg->position == 223)
                                                        {
                                                            player[i].chess[2].has_finished = 1;
                                                            player[i].goal_achieved++;
                                                            cout << "PLAYER " << i + 1 << " 的飞机到达终点，玩家目前得分为" << player[i].goal_achieved << "分\n";
                                                        }
                                                        for (int i1 = 0; i1 < 4; i1++)
                                                        {
                                                            if (i1 == i)
                                                                continue;
                                                            else
                                                                for (int j1 = 0; j1 < 4; j1++)
                                                                {
                                                                    if (player[i1].chess[j1].chess_ground == player[i].chess[2].chess_ground)
                                                                    {
                                                                        player[i1].chess[j1].chess_ground = &airport[i1*4 + j1];
                                                                        player[i1].chess[j1].is_off = 0;
                                                                        cout << "PLAYER " << i1 + 1 << " 的" << j1 + 1 << "号飞机被 PLAYER " << i + 1 << " 的飞机追上，返回机场\n";
                                                                    }
                                                                }
                                                        }
                                                        show_move(player);
                                                        cout << "PLAYER " << i + 1 << " 选择将" << 3 << "号飞机前进6格\n";
                                                    }
                                                    else
                                                    {
                                                        cout << "该飞机已到达终点，请重新选择\n";
                                                    }

                                                }
                                                if (msg.x >= 1000 && msg.x <= 1100 && msg.y >= 550 && msg.y <= 610)
                                                {
                                                    if (player[i].chess[3].has_finished == 0)
                                                    {
                                                        f1 = 1;
                                                        player[i].chess[3].move(6);
                                                        Ground* cg = player[i].chess[3].chess_ground;
                                                        if (cg->position == 205 || cg->position == 211 || cg->position == 217 || cg->position == 223)
                                                        {
                                                            player[i].chess[3].has_finished = 1;
                                                            player[i].goal_achieved++;
                                                            cout << "PLAYER " << i + 1 << " 的飞机到达终点，玩家目前得分为" << player[i].goal_achieved << "分\n";

                                                        }
                                                        for (int i1 = 0; i1 < 4; i1++)
                                                        {
                                                            if (i1 == i)
                                                                continue;
                                                            else
                                                                for (int j1 = 0; j1 < 4; j1++)
                                                                {
                                                                    if (player[i1].chess[j1].chess_ground == player[i].chess[3].chess_ground)
                                                                    {
                                                                        player[i1].chess[j1].chess_ground = &airport[i1*4 + j1];
                                                                        player[i1].chess[j1].is_off = 0;
                                                                        cout << "PLAYER " << i1 + 1 << " 的" << j1 + 1 << "号飞机被 PLAYER " << i + 1 << " 的飞机追上，返回机场\n";
                                                                    }
                                                                }
                                                        }
                                                        show_move(player);
                                                        cout << "PLAYER " << i + 1 << " 选择将" << 4 << "号飞机前进6格\n";
                                                    }
                                                    else
                                                    {
                                                        cout << "该飞机已到达终点，请重新选择\n";
                                                    }
                                                }
                                                break;
                                            default:
                                                break;
                                            }

                                            if (f1 == 1)
                                                break;
                                        }
                                    }
                                }
                                
                            }
                            // 骰子不为 6
                            else
                            {
                                int num_off = 0;
                                int num_finished = 0;
                                for (int j = 0; j < 4; j++)
                                {
                                    if (player[i].chess[j].is_off == 1)
                                        num_off++;
                                    if (player[i].chess[j].has_finished == 1)
                                        num_finished++;
                                }


                                if (num_off == 0)
                                {
                                    cout << "PLAYER " << i + 1 << " 飞机均未起飞，没有可以移动的飞机\n";
                                }
                                else if (num_finished == num_off)
                                {
                                    cout << "PLAYER " << i + 1 << " 目前没有可移动的飞机\n";
                                }
                                else
                                {
                                    cout << "PLAYER " << i + 1 << " 请选择前进的飞机\n";
                                    // 获取鼠标事件，选飞机循环
                                    while (1)
                                    {
                                        int f1 = 0;
                                        if (peekmessage(&msg, EM_MOUSE))
                                        {
                                            switch (msg.message)
                                            {
                                            case WM_LBUTTONDOWN:
                                                if (msg.x >= 800 && msg.x <= 900 && msg.y >= 450 && msg.y <= 510)
                                                {
                                                    if (player[i].chess[0].is_off == 1 && player[i].chess[0].has_finished == 0)
                                                    {
                                                        f1 = 1;
                                                        player[i].chess[0].move(a);
                                                        Ground* cg = player[i].chess[0].chess_ground;
                                                        if (cg->position == 205 || cg->position == 211 || cg->position == 217 || cg->position == 223)
                                                        {
                                                            player[i].chess[0].has_finished = 1;
                                                            player[i].goal_achieved++;
                                                            cout << "PLAYER " << i + 1 << " 的飞机到达终点，玩家目前得分为" << player[i].goal_achieved << "分\n";

                                                        }
                                                        for (int i1 = 0; i1 < 4; i1++)
                                                        {
                                                            if (i1 == i)
                                                                continue;
                                                            else
                                                                for (int j1 = 0; j1 < 4; j1++)
                                                                {
                                                                    if (player[i1].chess[j1].chess_ground == player[i].chess[0].chess_ground)
                                                                    {
                                                                        player[i1].chess[j1].chess_ground = &airport[i1*4 + j1];
                                                                        player[i1].chess[j1].is_off = 0;
                                                                        cout << "PLAYER " << i1 + 1 << " 的" << j1 + 1 << "号飞机被 PLAYER " << i + 1 << " 的飞机追上，返回机场\n";
                                                                    }
                                                                }
                                                        }
                                                        show_move(player);
                                                        cout << "PLAYER " << i + 1 << " 选择将" << 1 << "号飞机前进" << a << "格\n";
                                                    }
                                                    else if (player[i].chess[0].is_off == 0)
                                                    {
                                                        cout << "该飞机还未起飞，目前不可移动。请重新选择\n";
                                                    }
                                                    else
                                                    {
                                                        cout << "该飞机已到达终点，请重新选择\n";
                                                    }
                                                }
                                                if (msg.x >= 800 && msg.x <= 900 && msg.y >= 550 && msg.y <= 610)
                                                {
                                                    if (player[i].chess[1].is_off == 1 && player[i].chess[1].has_finished == 0)
                                                    {
                                                        f1 = 1;
                                                        player[i].chess[1].move(a);
                                                        Ground* cg = player[i].chess[1].chess_ground;
                                                        if (cg->position == 205 || cg->position == 211 || cg->position == 217 || cg->position == 223)
                                                        {
                                                            player[i].chess[1].has_finished = 1;
                                                            player[i].goal_achieved++;
                                                            cout << "PLAYER " << i + 1 << " 的飞机到达终点，玩家目前得分为" << player[i].goal_achieved << "分\n";

                                                        }
                                                        for (int i1 = 0; i1 < 4; i1++)
                                                        {
                                                            if (i1 == i)
                                                                continue;
                                                            else
                                                                for (int j1 = 0; j1 < 4; j1++)
                                                                {
                                                                    if (player[i1].chess[j1].chess_ground == player[i].chess[1].chess_ground)
                                                                    {
                                                                        player[i1].chess[j1].chess_ground = &airport[i1*4 + j1];
                                                                        player[i1].chess[j1].is_off = 0;
                                                                        cout << "PLAYER " << i1 + 1 << " 的" << j1 + 1 << "号飞机被 PLAYER " << i + 1 << " 的飞机追上，返回机场\n";
                                                                    }
                                                                }
                                                        }
                                                        show_move(player);
                                                        cout << "PLAYER " << i + 1 << " 选择将" << 2 << "号飞机前进" << a << "格\n";
                                                    }
                                                    else if (player[i].chess[1].is_off == 0)
                                                    {
                                                        cout << "该飞机还未起飞，目前不可移动。请重新选择\n";
                                                    }
                                                    else
                                                    {
                                                        cout << "该飞机已到达终点，请重新选择\n";
                                                    }
                                                }
                                                if (msg.x >= 1000 && msg.x <= 1100 && msg.y >= 450 && msg.y <= 510)
                                                {
                                                    if (player[i].chess[2].is_off == 1 && player[i].chess[2].has_finished == 0)
                                                    {
                                                        f1 = 1;
                                                        player[i].chess[2].move(a);
                                                        Ground* cg = player[i].chess[2].chess_ground;
                                                        if (cg->position == 205 || cg->position == 211 || cg->position == 217 || cg->position == 223)
                                                        {
                                                            player[i].chess[2].has_finished = 1;
                                                            player[i].goal_achieved++;
                                                            cout << "PLAYER " << i + 1 << " 的飞机到达终点，玩家目前得分为" << player[i].goal_achieved << "分\n";

                                                        }
                                                        for (int i1 = 0; i1 < 4; i1++)
                                                        {
                                                            if (i1 == i)
                                                                continue;
                                                            else
                                                                for (int j1 = 0; j1 < 4; j1++)
                                                                {
                                                                    if (player[i1].chess[j1].chess_ground == player[i].chess[2].chess_ground)
                                                                    {
                                                                        player[i1].chess[j1].chess_ground = &airport[i1*4 + j1];
                                                                        player[i1].chess[j1].is_off = 0;
                                                                        cout << "PLAYER " << i1 + 1 << " 的第" << j1 + 1 << "架飞机被 PLAYER " << i + 1 << " 的飞机追上，返回机场\n";
                                                                    }
                                                                }
                                                        }
                                                        show_move(player);
                                                        cout << "PLAYER " << i + 1 << " 选择将" << 3 << "号飞机前进" << a << "格\n";
                                                    }
                                                    else if (player[i].chess[2].is_off == 0)
                                                    {
                                                        cout << "该飞机还未起飞，目前不可移动。请重新选择\n";
                                                    }
                                                    else
                                                    {
                                                        cout << "该飞机已到达终点，请重新选择\n";
                                                    }
                                                }
                                                if (msg.x >= 1000 && msg.x <= 1100 && msg.y >= 550 && msg.y <= 610)
                                                {
                                                    if (player[i].chess[3].is_off == 1 && player[i].chess[3].has_finished == 0)
                                                    {
                                                        f1 = 1;
                                                        player[i].chess[3].move(a);
                                                        Ground* cg = player[i].chess[3].chess_ground;
                                                        if (cg->position == 205 || cg->position == 211 || cg->position == 217 || cg->position == 223)
                                                        {
                                                            player[i].chess[3].has_finished = 1;
                                                            player[i].goal_achieved++;
                                                            cout << "PLAYER " << i + 1 << " 的飞机到达终点，玩家目前得分为" << player[i].goal_achieved << "分\n";

                                                        }
                                                        for (int i1 = 0; i1 < 4; i1++)
                                                        {
                                                            if (i1 == i)
                                                                continue;
                                                            else
                                                                for (int j1 = 0; j1 < 4; j1++)
                                                                {
                                                                    if (player[i1].chess[j1].chess_ground == player[i].chess[3].chess_ground)
                                                                    {
                                                                        player[i1].chess[j1].chess_ground = &airport[i1*4 + j1];
                                                                        player[i1].chess[j1].is_off = 0;
                                                                        cout << "PLAYER " << i1 + 1 << " 的第" << j1 + 1 << "架飞机被 PLAYER " << i + 1 << " 的飞机追上，返回机场\n";
                                                                    }
                                                                }
                                                        }
                                                        show_move(player);
                                                        cout << "PLAYER " << i + 1 << " 选择将" << 4 << "号飞机前进" << a << "格\n";
                                                    }
                                                    else if (player[i].chess[3].is_off == 0)
                                                    {
                                                        cout << "该飞机还未起飞，目前不可移动。请重新选择\n";
                                                    }
                                                    else
                                                    {
                                                        cout << "该飞机已到达终点，请重新选择\n";
                                                    }
                                                }
                                                break;
                                            default:
                                                break;
                                            }

                                            if (f1 == 1)
                                                break;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    default:
                        break;
                    }
                }

                if (f == 1)
                    break;
            }

            if (player[i].goal_achieved == 4)
            {
                winner = i + 1;
                break;
            }
        }
        if (winner != -1)
        {
            Sleep(1000);
            show_winner(winner);
            cout << "——————————恭喜PLAYER " << winner << "获得最终胜利！！！——————————\n";
            cout << "游戏将在10秒后自动退出\n";
            break;
        }

            

        for (int i = player_num; i < total_num; i++) // 每回合电脑玩家循环
        {
            Sleep(2000);
            int f = 0;
            while (1)
            {
                f = 1;
                int a;
                if (debug == 1)
                {
                    cout << "请输入这次摇到的点数: ";
                    cin >> a;
                }
                else
                    a = roll_dice(i, player);
                set_fill_color(player[i]);
                fillrectangle(950, 60, 990, 100);
                show_dice(a);

                if (a == 6)
                {
                    int all_off = 1;
                    for (int j = 0; j < 4; j++)
                        if (player[i].chess[j].is_off == 0)
                            all_off = 0;
                    // 骰子为 6 且有飞机未起飞
                    if (all_off == 0)
                    {
                        cout << "PLAYER " << i + 1 << "（电脑） 将选择一架飞机进入跑道\n";
                        Sleep(2000);
                        for (int j = 0; j < 4; j++)
                        {
                            if (player[i].chess[j].is_off == 0)
                            {
                                player[i].chess[j].set_off();
                                show_move(player);
                                cout << "PLAYER " << i + 1 << "（电脑） 选择将" << j + 1 << "号飞机进入跑道\n";
                                break;
                            }
                        }
                        cout << "PLAYER " << i + 1 << "（电脑） 可以再掷一次骰子\n";
                        f = 0;
                    }
                    // 骰子未 6 且飞机全都起飞
                    else
                    {
                        cout << "PLAYER " << i + 1 << "（电脑） 将选择前进的飞机\n";
                        Sleep(2000);
                        for (int j = 0; j < 4; j++)
                        {
                            if (player[i].chess[j].has_finished == 0)
                            {
                                cout << "PLAYER " << i + 1 << "（电脑） 选择将" << j + 1 << "号飞机前进" << 6 << "格\n";
                                player[i].chess[j].move(6);
                                Ground* cg = player[i].chess[j].chess_ground;
                                if (cg->position == 205 || cg->position == 211 || cg->position == 217 || cg->position == 223)
                                {
                                    player[i].chess[j].has_finished = 1;
                                    player[i].goal_achieved++;
                                    cout << "PLAYER " << i + 1 << "（电脑） 的飞机到达终点，玩家目前得分为" << player[i].goal_achieved << "分\n";

                                }
                                for (int i1 = 0; i1 < 4; i1++)
                                {
                                    if (i1 == i)
                                        continue;
                                    else
                                        for (int j1 = 0; j1 < 4; j1++)
                                        {
                                            if (player[i1].chess[j1].chess_ground == player[i].chess[j].chess_ground)
                                            {
                                                player[i1].chess[j1].chess_ground = &airport[i1 * 4 + j1];
                                                player[i1].chess[j1].is_off = 0;
                                                cout << "PLAYER " << i1 + 1 << " 的第" << j1 + 1 << "架飞机被 PLAYER " << i + 1 << " 的飞机追上，返回机场\n";
                                            }
                                        }
                                }
                                show_move(player);
                                break;
                            }
                        }
                    }
                }
                // 骰子不为 6
                else
                {
                    int num_off = 0;
                    int num_finish = 0;
                    for (int j = 0; j < 4; j++)
                    {
                        if (player[i].chess[j].is_off == 1)
                            num_off++;
                        if (player[i].chess[j].has_finished == 1)
                            num_finish++;
                    }
                        

                    if (num_off == 0)
                    {
                        cout << "PLAYER " << i + 1 << "（电脑） 飞机均未起飞，没有可以移动的飞机\n";
                    }
                    else if (num_off == num_finish)
                    {
                        cout << "PLAYER " << i + 1 << "（电脑） 目前没有可以移动的飞机\n";
                    }
                    else
                    {
                        cout << "PLAYER " << i + 1 << "（电脑） 将选择前进的飞机\n";
                        Sleep(2000);
                        for (int j = 0; j < 4; j++)
                        {
                            if (player[i].chess[j].is_off == 1 && player[i].chess[j].has_finished == 0)
                            {
                                player[i].chess[j].move(a);
                                Ground* cg = player[i].chess[j].chess_ground;
                                if (cg->position == 205 || cg->position == 211 || cg->position == 217 || cg->position == 223)
                                {
                                    player[i].chess[j].has_finished = 1;
                                    player[i].goal_achieved++;
                                    cout << "PLAYER " << i + 1 << "（电脑） 的飞机到达终点，玩家目前得分为" << player[i].goal_achieved << "分\n";

                                }
                                for (int i1 = 0; i1 < 4; i1++)
                                {
                                    if (i1 == i)
                                        continue;
                                    else
                                        for (int j1 = 0; j1 < 4; j1++)
                                        {
                                            if (player[i1].chess[j1].chess_ground == player[i].chess[j].chess_ground)
                                            {
                                                player[i1].chess[j1].chess_ground = &airport[i1 * 4 + j1];
                                                player[i1].chess[j1].is_off = 0;
                                                cout << "PLAYER " << i1 + 1 << " 的第" << j1 + 1 << "架飞机被 PLAYER " << i + 1 << " 的飞机追上，返回机场\n";
                                            }
                                        }
                                }
                                show_move(player);
                                cout << "PLAYER " << i + 1 << "（电脑） 选择将" << j + 1 << "号飞机前进" << a << "格\n";
                                break;
                            }
                        }
                    }
                }

                if (f == 1)
                    break;
            }
        
            if (player[i].goal_achieved == 4)
            {
                winner = i + 1;
                break;
            }
        }

        if (winner != -1)
        {
            Sleep(1000);
            show_winner(winner);
            cout << "——————————恭喜PLAYER " << winner << "（电脑） 获得最终胜利！！！——————————\n";
            cout << "游戏将在10秒后自动退出\n";
            break;
        }
    }
 



    Sleep(10000);
    closegraph();
    return 0;
}
