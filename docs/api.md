# API Endpoints

### `GET /health`

**Returns** `ok` with status code 200 if the server is up.

### `POST /auth/login`

**Expected JSON**:

| Field | Type |
|-------|------|
| username | string |
| password | string |

**Returns** a `User` and 200 status on success.

**Returns** an error message and 401 status code upon invalid username/password.

### `POST /auth/addUser`

**Expected JSON**:

| Field | Type |
|-------|------|
| username | string |
| password | string |
| metadata | dictionary<string, string>? |

**Returns** a `User` and 200 status upon successful creation.

**Returns** error message and 400 status code if field is missing, or user already exists.

### `GET /group/{id}`

**Expect** `id` to be an integer.

**Returns** a `Group` and 200 status code if group with id `id` is found.

**Returns** 404 status code if group exist.

### `POST /group`

**Expected JSON**

| Field | Type |
|-------|------|
| name | string |
| metadata | dictionary<string, string>? |

**Returns** a `Group` if group was able to be created.

**Returns** 400 status code if group name already is in use.

## Schemas

### `User`

| Field | Type |
|-------|------|
| id | UUID (string) |
| username | string |
| metadata | dictionary<string, string> |

### `Group`

| Field | Type |
|-------|------|
| id | UUID (string) |
| name | string |
| metadata | dictionary<string, string> |
