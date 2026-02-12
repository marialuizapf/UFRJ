from flask import Flask, request, jsonify
import sqlite3
import os
from modelos import SATRecord
import db 
app = Flask(__name__)

# Cria o banco caso não exista
if not os.path.isfile('Database.db'):
    db.init_db()

@app.route('/')
def index():
    return jsonify({
        'msg': 'API de Escolas SAT Online 🎓',
        'status': '200',
        'rotas': {
            'GET': '/request ou /request/<DBN>',
            'POST': '/request',
            'PUT': '/request',
            'DELETE': '/request/<DBN>'
        }
    })

@app.route('/request', methods=['GET'])
def get_all():
    escolas = [e.serialize() for e in db.list_all()]
    return jsonify({
        'res': escolas,
        'msg': 'Lista de todas as escolas!',
        'status': '200',
        'count': len(escolas)
    })

@app.route('/request/<dbn>', methods=['GET'])
def get_by_dbn(dbn):
    escola = db.get_by_dbn(dbn)
    if escola:
        return jsonify({
            'res': escola.serialize(),
            'msg': f'Escola com DBN {dbn} encontrada!',
            'status': '200'
        })
    return jsonify({
        'res': '',
        'msg': f'Erro ! Escola com DBN {dbn} não encontrada.',
        'status': '404'
    })

@app.route('/request', methods=['POST'])
def criar():
    data = request.get_json()
    dbn = data.get('DBN')
    if db.get_by_dbn(dbn):
        return jsonify({
            'res': '',
            'msg': f'Erro ! Escola com DBN {dbn} já existe!',
            'status': '409'
        })
    try:
        escola = SATRecord(**data)
        db.create(escola)
        return jsonify({
            'res': escola.serialize(),
            'msg': 'Escola criada com sucesso! ',
            'status': '201'
        })
    except Exception as e:
        return jsonify({
            'res': '',
            'msg': f'Erro ao criar escola: {str(e)}',
            'status': '400'
        })

@app.route('/request', methods=['PUT'])
def atualizar():
    data = request.get_json()
    dbn = data.get('DBN')
    escola = db.get_by_dbn(dbn)
    if not escola:
        return jsonify({
            'res': '',
            'msg': f'Erro ! Escola com DBN {dbn} não encontrada!',
            'status': '404'
        })
    for k, v in data.items():
        setattr(escola, k, v)
    db.update(escola)
    return jsonify({
        'res': escola.serialize(),
        'msg': f'Escola {dbn} atualizada com sucesso! ',
        'status': '200'
    })

@app.route('/request/<dbn>', methods=['DELETE'])
def deletar(dbn):
    escola = db.get_by_dbn(dbn)
    if not escola:
        return jsonify({
            'res': '',
            'msg': f'Erro ! Escola com DBN {dbn} não encontrada!',
            'status': '404'
        })
    db.delete(dbn)
    return jsonify({
        'res': '',
        'msg': f'Escola {dbn} removida com sucesso! ',
        'status': '200'
    })

if __name__ == '__main__':
    app.run(debug=True)
