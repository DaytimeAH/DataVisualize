#include "graphgraphicsview.h"
#include <QTextStream>

GraphGraphicsView::GraphGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    setScene(&scene);
    resize(1000,500);
    setBackgroundBrush(Qt::white);
    setFocus();

    QLinearGradient linearGrad(-500, -500, 500, 500); // átmenetes ecset
    linearGrad.setColorAt(0, QColor(255, 255, 255));
    linearGrad.setColorAt(1, QColor(192, 192, 192));
    setBackgroundBrush(linearGrad);
    setRenderHint(QPainter::Antialiasing);
    setFrameStyle(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    qsrand(QTime::currentTime().msec());

    randomGraph();

    dDialog = new dijkstraDialog();
    source = -1;
    destination = -1;

    QObject::connect(dDialog, SIGNAL(runDijkstraFromTo(int,int)),
                     this, SLOT(runDijkstra(int,int)));
}

void GraphGraphicsView::drawPath(NodeGraphicsItem *from, NodeGraphicsItem *to)
{
    QPen pen(QColor(qrand()%256,qrand()%256,qrand()%256));

    double Pi = 3.1415926535897932384626433832795028;
    qreal x1, x2, y1, y2;
    if (isBelow(from, to))
    {
        x1 = from->pos().x()+15;
        y1 = from->pos().y()+10;
        x2 = to->pos().x()+15;
        y2 = to->pos().y()-20;
    }
    else
    {
        x1 = from->pos().x()+15;
        y1 = from->pos().y()-20;
        x2 = to->pos().x()+15;
        y2 = to->pos().y()+10;
    }

    lines.push_back(scene.addLine(x1, y1,
                                  x2, y2,pen));
    qreal arrowsize = 15;
    QGraphicsLineItem* line = lines.last();


    // I HAVE NO IDEA WHAT I'M CALCULATING MODE ON

    double angle = ::acos(line->line().dx() / line->line().length());

    if (line->line().dy() >= 0)
             angle = (Pi * 2) - angle;

    QPointF arrowP1 = line->line().p1()  + QPointF(sin(angle + Pi / 3 ) * arrowsize,
                                                   cos(angle+Pi/3)*arrowsize);
    QPointF arrowP2 = line->line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowsize,
                                            cos(angle + Pi - Pi / 3) * arrowsize);

    // I HAVE NO IDEA WHAT I'M CALCULATING MODE OFF


    arrows.push_back(scene.addLine(line->line().p1().x(), line->line().p1().y(),
                                   arrowP1.x(), arrowP1.y(),pen));
    arrows.push_back(scene.addLine(line->line().p1().x(), line->line().p1().y(),
                                   arrowP2.x(), arrowP2.y(),pen));
}

void GraphGraphicsView::drawAllEdges()
{
    for (int i = 0; i < adj.length(); ++i) {
        adj[i].First();
        while(adj[i].Current() != 0)
        {
            drawPath(nodes[adj[i].Current()->Dest], nodes[i]);
            adj[i].Next();
        }
    }
}

void GraphGraphicsView::clearNodes(bool Permanent)
{
    for (int i = 0; i < nodes.length(); ++i) {
        scene.removeItem(nodes[i]);
    }
    if (Permanent) {
        nodes.clear();
    }
}

void GraphGraphicsView::clearArrows(bool Permanent)
{
    for (int i = 0; i < lines.length(); ++i) {
        scene.removeItem(lines[i]);
    }

    for (int i = 0; i < arrows.length(); ++i) {
        scene.removeItem(arrows[i]);
    }

    if(Permanent)
    {
        lines.clear();
        arrows.clear();
    }
}

bool GraphGraphicsView::isBelow(NodeGraphicsItem *item, NodeGraphicsItem *toCheck)
{
    return item->pos().y() < toCheck->pos().y();
}

void GraphGraphicsView::reposition()
{
    if (nodes.length() == 0)
        return;
    qsrand(QTime::currentTime().msec());
    for (int i = 0; i < lines.length(); ++i) {
        scene.removeItem(lines[i]);
    }
    lines.clear();
    for (int i = 0; i < arrows.length(); ++i) {
        scene.removeItem(arrows[i]);
    }
    arrows.clear();
    for (int i = 0; i < weights.size(); ++i) {
        scene.removeItem(weights[i]);
    }
    weights.clear();

    for (int i = 0; i < nodes.length(); ++i)
    {
        NodeGraphicsItem* item = nodes[i];
        qreal powX;
        qreal powY = qPow(-1,i);
        if (qrand() % 2)
            powX = -1;
        else
            powX = 1;
        item->setPos(powX * (qrand() % 450), powY * (qrand() % 220));

        bool tooClose = false;
        for (int j = 0; j < nodes.length(); ++j)
        {
            if (i != j)
            {
                tooClose = tooClose || itemLevelTooClose(nodes[j], item);
                //qDebug() << "tooClose " << tooClose;
            }
        }
        while(tooClose)
        {
            tooClose = false;
            //qDebug() << "too close";
            item->setPos(powX * (qrand() % 450), powY * (qrand() % 220));
            for (int j = 0; j < nodes.length(); ++j) {
                if (i != j)
                {
                    tooClose = tooClose || itemLevelTooClose(nodes[j], item);
                }
            }
        }
    }

    drawAllEdges();
    drawWeights();
}

void GraphGraphicsView::clear()
{
    clearNodes();
    clearArrows();
    clearWeights();
}

void GraphGraphicsView::preDijkstra()
{
    dDialog->setSize(adjMatrix.length());
    dDialog->show();
}

void GraphGraphicsView::runDijkstra(int from, int to)
{
    Dijkstra(from, to);
}

void GraphGraphicsView::drawWeights()
{
    int lineInd = 0;
    int offset = 16;


    for (int i = 0; i < adj.length(); ++i) {
        adj[i].First();
        while(adj[i].Current() != 0)
        {
            if(i < adj[i].Current()->Dest)
            {
                offset = -16;
            }
            else
            {
                offset = 16;
            }
            weights.push_back(scene.addText(QString::number(adj[i].Current()->Weight)));
            weights.last()->setPos((lines[lineInd]->line().x1() + lines[lineInd]->line().x2()) / 2,
                                   (lines[lineInd]->line().y1() + lines[lineInd]->line().y2() + offset) / 2);
            lineInd++;
            adj[i].Next();
        }
    }
}

void GraphGraphicsView::readFromFile()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open file..."),
            QDir::currentPath(),
            tr("Text files (*.txt)"));
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream stream(&file);


    clear();
    adj.clear();
    adjMatrix.clear();

    int ind = 0;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QList<QString> elem = line.split(" ");
        adj.push_back(AdjacencyList());
        for (int i = 2; i < elem.length(); ++i) {
            adj[ind].Insert(elem[i].toInt(), (qrand() % 7) + 1);
            qDebug() << ind << elem[i];
        }
        qDebug() << line;
        nodes.push_back(new NodeGraphicsItem(elem[0]));
        scene.addItem(nodes[ind]);
        ind++;
    }

    for (int i = 0; i < adj.length(); ++i) {
        adjMatrix.push_back(QList<int>());
        for (int j = 0; j < adj.length(); ++j) {
            adjMatrix[i].push_back(0);
        }
    }
    qDebug() << adj.length() << nodes.length() << adjMatrix.length() << ind;

    for (int i = 0; i < adj.length(); ++i) {
        adj[i].First();
        adj[i].printValues();
        while(adj[i].Current() != 0)
        {
            adjMatrix[i][adj[i].Current()->Dest] = adj[i].Current()->Weight;
            qDebug() << i << adj[i].Current()->Dest << " : " << adj[i].Current()->Weight;
            adj[i].Next();
        }
    }

    reposition();

}

void GraphGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_R) {
        reposition();
    }
    if (event->key() == Qt::Key_1)
    {
        randomGraph();
    }
}

void GraphGraphicsView::runPrim()
{
    minQ.empty();
    QList<int> prevs;
    QList<int> distances;
    for (int i = 0; i < nodes.length(); ++i) {
        distances.push_back(50000);
        prevs.push_back(-1);
        minQ.enqueue(distances[i],i);
    }
    qDebug() << 1;
    distances[0] = 0;
    minQ.replace(0,0);
    qDebug() << 2;

    while (minQ.count() > 0) {
        int ind  = minQ.dequeue();
        adj[ind].First();
        int dest = adj[ind].Current()->Dest;
        int weight = adj[ind].Current()->Weight;
        qDebug() << 3;
        while (adj[ind].Current() != 0) {
            if (distances[adj[ind].Current()->Dest] >=
                    adj[ind].Current()->Weight)
            {
                distances[dest] = weight;
                prevs[dest] = ind;
                minQ.replace(weight,dest);
            }
            adj[ind].Next();
        }
    }

    QString line;
    for (int i = 0; i < prevs.length(); ++i)
        line.append(QString::number(prevs[i])+ " ");
    qDebug() << line;

}

void GraphGraphicsView::mousePressEvent(QMouseEvent *event)
{
    /*
    qDebug() << "x :" << event->posF().x() << " y : " << event->posF().y();
    qDebug() << mapToScene(event->posF().x(), event->posF().y()).x() <<
                mapToScene(event->posF().x(), event->posF().y()).y();
                */
    for (int i = 0; i < nodes.length(); ++i) {
        qreal nodeX = nodes[i]->pos().x();
        qreal nodeY = nodes[i]->pos().y();
        qreal clickX = (mapToScene(event->pos().x(), event->pos().y())).x();
        qreal clickY = (mapToScene(event->pos().x(), event->pos().y())).y();

        if(clickX >= nodeX-35 && clickX <= nodeX + 35 && clickY <= nodeY + 15 && clickY >= nodeY - 15)
        {
            if (source == -1)
            {
                source = i;
                nodes[i]->setBrush(Qt::red);
                scene.update();
            }
            else if (source > -1 && destination == -1 && i != source)
            {
                destination = i;
                nodes[source]->setBrush(Qt::white);
                runDijkstra(source,destination);
                source = -1;
                destination = -1;
                scene.update();
            }
        }
    }
}

void GraphGraphicsView::depthFirstSearch()
{
    clearArrows();
    clearWeights();
    drawAllEdges();
    drawWeights();

    bool hasCircle = false;
    int depthNo = 1;
    int endNo = 1;
    QList<int> prev;

    for (int u = 0; u < nodes.length(); ++u) {
        nodes[u]->setDepthNo(0);
        nodes[u]->setEndNo(0);
        prev.push_back(-1);
    }

    for (int u = 0; u < nodes.length(); ++u) {
        if (nodes[u]->getDepthNo() == 0) {
            DFS(u,depthNo, endNo, prev, hasCircle);
        }
    }
    if (hasCircle) {
        QMessageBox::warning(0, "Warning","This graph has a circle.");
    }
    else
    {
        QMessageBox::information(0, "Done", "Sum of all weights: ");
    }

    scene.update();
}

void GraphGraphicsView::DFS(int curr, int &depthNo, int &endNo, QList<int>& prev, bool& hasCircle)
{
    nodes[curr]->setDepthNo(depthNo++);
    adj[curr].First();
    while(adj[curr].Current() != 0)
    {
        int dest = adj[curr].Current()->Dest;
        if (nodes[dest]->getDepthNo() == 0)
        {
            DFS(dest, depthNo, endNo, prev, hasCircle);
            prev[dest] = curr;
            qDebug() << nodes[curr]->getDepthNo() << nodes[dest]->getDepthNo() << nodes[dest]->getEndNo();
            if (nodes[curr]->getDepthNo() > nodes[dest]->getDepthNo() && nodes[dest]->getEndNo() == 0) {
                hasCircle = true;
            }
        }
        adj[curr].Next();
    }
    nodes[curr]->setEndNo(endNo++);
}

void GraphGraphicsView::CondMinSearch(QList<int> d, QList<bool> found, int& u, bool& l)
{
    l = false;
    for (int i = 0; i < d.length(); ++i) {
        if (!found[i] && !l) {
            u = i;
            l = true;
        }
        else if(!found[i] && l && d[i] < d[u])
        {
            u = i;
        }
    }
}

void GraphGraphicsView::Dijkstra(int s, int to)
{
    QList<int> d;
    QList<int> prev;
    QList<bool> found;
    int u;
    bool foundNext = false;
    for (int i = 0; i < nodes.length(); ++i) {
        d.push_back(50000);
        prev.push_back(-1);
        found.push_back(false);
    }

    d[s] = 0;
    CondMinSearch(d,found,u,foundNext);

    while(foundNext)
    {
        found[u] = true;
        for (int v = 0; v < adjMatrix.length(); ++v) {
            if (adjMatrix[u][v] != 0 && !found[v] && d[u] + adjMatrix[u][v] < d[v]) {
                d[v] = d[u] + adjMatrix[u][v];
                prev[v] = u;
            }
        }
        CondMinSearch(d,found,u,foundNext);
    }
    prevs = prev;
    QString prevString;
    for (int i = 0; i < prevs.length(); ++i) {
        prevString.append(QString::number(prevs[i]) + " ");
    }
    //qDebug() << prevString;
    drawShortestPath(s, to);
}



bool GraphGraphicsView::itemLevelTooClose(NodeGraphicsItem *first, NodeGraphicsItem *second)
{
    qreal diffY = qAbs(first->pos().y() - second->pos().y());
    qreal diffX = qAbs(first->pos().x() - second->pos().x());
    return (diffY < 30 || diffX < 50) && this->nodes.length() < 10;
}


void GraphGraphicsView::randomGraph()
{
    clearNodes();
    clearArrows();

    adjMatrix.clear();
    adj.clear();


    int sizeOf = qrand() % 8;

    for (int i = 0; i < sizeOf; ++i) {
        adjMatrix.push_back(QList<int>());
        adj.push_back(AdjacencyList());
        for (int j = 0; j < sizeOf; ++j) {
            if (i != j)
            {
                int val = qrand() % 50;
                if ((val % 10) == 0)
                    val = 0;
                adjMatrix[i].push_back(val);
                if (val > 0) {
                    adj[i].Insert(j,val);

                }
            }
        }
        nodes.push_back(new NodeGraphicsItem(QString::number(i+1)));
        scene.addItem(nodes[i]);
        //qDebug() << i+1 << ": " << adj[i].printValues();
        //adj[i].printValues();
        nodes[i]->setPos(qrand() % 500, qrand() % 500);
    }

    reposition();
    //runPrim();
}

void GraphGraphicsView::drawSpecifiedGraph(int vertices, int edges)
{
    clearNodes();
    clearArrows();
    adjMatrix.clear();
    adj.clear();

    for (int i = 0; i < vertices; ++i) {
        nodes.push_back(new NodeGraphicsItem(QString::number(i+1)));
        scene.addItem(nodes[i]);
        nodes[i]->setPos(qrand() % 500, qrand() % 500);
    }

    for (int i = 0; i < nodes.length(); ++i) {
        adjMatrix.push_back(QList<int>());
        adj.push_back(AdjacencyList());
        for (int j = 0; j < nodes.length(); ++j) {
            if (edges > 0 && i != j)
            {
                int val = qrand() % 11;
                adjMatrix[i].push_back(val);
                if (val > 0) {
                    adj[i].Insert(j,val);
                }
                edges--;
            }
        }
        //adj[i].printValues();
    }

    reposition();
}

void GraphGraphicsView::clearWeights()
{
    for (int i = 0; i < weights.length(); ++i) {
        scene.removeItem(weights[i]);
    }
    weights.clear();
}

void GraphGraphicsView::drawShortestPath(int from, int to)
{
    clearArrows();
    clearWeights();
    int next = prevs[to];
    while(next != from)
    {
        drawPath(nodes[to],nodes[next]);
        to = next;
        next = prevs[next];
    }
    drawPath(nodes[to],nodes[next]);

}

void GraphGraphicsView::drawSpecifiedGraph(QList<QList<int> > adjM)
{
    if(&adjM != &adjMatrix)
    {
        clearNodes();
        clearArrows();
        adjMatrix.clear();
        adj.clear();
        adjMatrix = adjM;

        for (int i = 0; i < adjMatrix.length(); ++i) {
            adj.push_back(AdjacencyList());
            for (int j = 0; j < adjMatrix.length(); ++j) {
                if (adjMatrix[i][j] > 0) {
                    adj[i].Insert(j, adjMatrix[i][j]);
                }
            }
        }
    }

    for (int i = 0; i < adjMatrix.size(); ++i) {
        nodes.push_back(new NodeGraphicsItem(QString::number(i+1)));
        scene.addItem(nodes[i]);
        nodes[i]->setPos(qrand() % 500, qrand() % 500);
    }
    reposition();
}

