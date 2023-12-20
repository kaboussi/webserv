#include "Expr.hpp"

MainContext::MainContext() : _left(NULL), _right(NULL) {}

MainContext::MainContext(Expr* left, Expr* right) : _left(left), _right(right) {
}

MainContext::MainContext(const MainContext& mainContext)
    : _left(NULL)
    , _right(NULL)
{
    if (mainContext._left) {
        _left = new MainContext();
        *_left = *mainContext._left;
    }
    if (mainContext._right) {
        _right = new MainContext();
        *_right = *mainContext._right;
    }
}

MainContext::~MainContext() {
    delete _left;
    delete _right;
}

MainContext&    MainContext::operator=(const MainContext& mainContext) {
    _swap(mainContext);
    return *this;
}

void    MainContext::accept(Visitor& visitor) {
    visitor.visitMainContextExpr(*this);
}

Expr*   MainContext::getLeftExpr() { return _left; }

Expr*   MainContext::getRightExpr() { return _right; }

void    MainContext::_swap(MainContext mainContext) {
    Expr*   left = mainContext._left;
    Expr*   right = mainContext._right;

    mainContext._left = _left;
    mainContext._right = _right;
    _left = left;
    _right = right;
}

//MainContext::MainContext() : _leftExpr(NULL), _rightExpr(NULL) {}

//MainContext::MainContext(Expr* left, Expr* right)
//    : _leftExpr(left)
//    , _rightExpr(right)
//{
//}

//MainContext::MainContext(const MainContext& mc)
//    : _leftExpr(NULL)
//    , _rightExpr(NULL)
//{
//    if (mc._leftExpr) {
//        _leftExpr = new MainContext();
//        *_leftExpr = *mc._leftExpr;
//    }
//    if (mc._rightExpr) {
//        _rightExpr = new MainContext();
//        *_rightExpr = *mc._rightExpr;
//    }
//}

//MainContext&    MainContext::operator=(const MainContext& mc) {
//    swap(mc);
//    return *this;
//}

//MainContext::~MainContext() {
//    delete _leftExpr;
//    _leftExpr = NULL;
//    delete _rightExpr;
//    _rightExpr = NULL;
//}

//void    MainContext::swap(MainContext mc) {
//    Expr*   tempLeft = mc._leftExpr;
//    Expr*   tempRight = mc._rightExpr;

//    mc._leftExpr = _leftExpr;
//    mc._rightExpr = _rightExpr;
//    _leftExpr = tempLeft;
//    _rightExpr = tempRight;
//}

//void    MainContext::accept(Visitor& visitor, HttpConfig& conf) {
//    visitor.visitMainContextExpr(*this, conf);
//}

//Expr*   MainContext::getLeftExpr() { return _leftExpr; }

//Expr*   MainContext::getRightExpr() { return _rightExpr; }